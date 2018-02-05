/**
 * Yue Hao
 * yuh63@pitt.edu
 * 2/4/2018
 * CS1550
 */
 
// header files included
#include <linux/fb.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

// global variables
int fd;
unsigned short *fb_ptr;
unsigned long xlen;
unsigned long ylen;
unsigned long size;
typedef unsigned short color_t;

// function prototypes
void init_graphics();
void exit_graphics();
void clear_screen();
char getkey();
void sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void draw_circle(int x, int y, int r, color_t color);

void init_graphics(){
	// initiate the graphics 
	struct fb_fix_screeninfo fix_info;
	struct fb_var_screeninfo var_info;
	struct termios term;
	fd = open ("/dev/fb0", O_RDWR);
	ioctl (fd, FBIOGET_VSCREENINFO, &var_info);
	ioctl (fd, FBIOGET_FSCREENINFO, &fix_info);
	xlen = var_info.xres_virtual;
	ylen = var_info.yres_virtual;
	size = fix_info.line_length;;
	//mmap the framebuffer
	fb_ptr = (unsigned short*)mmap(NULL, xlen * size, PROT_WRITE, MAP_SHARED, fd, 0);
	//ioctl to disable echo and buffering the keypresses
	ioctl(STDIN_FILENO, TCGETS, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	ioctl(STDIN_FILENO, TCSETS, &term);
}

//exit the graphics device
void exit_graphics(){
	//unsetting echo and keypress buffer
	struct termios term;
	//unmap framme buffer
	munmap(fb_ptr, ylen * size);
	ioctl(STDIN_FILENO, TCGETS, &term);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	ioctl(STDIN_FILENO, TCSETS, &term);
	close(fd);
}

//clear screen using escape codes 
void clear_screen(){
	write(1, "\033[2J", 10);
}

//read key characters
char getkey(){
	char input;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	struct timeval wait;
	wait.tv_sec = 5;
	wait.tv_usec = 0;
	int selectchar = select(STDIN_FILENO+1, &rfds, NULL, NULL, &wait);
	// whenever there's a char in buffer, 
	if(selectchar){
		read(0, &input, sizeof(input));
	}
	return input;
}

//function to make program sleep
void sleep_ms(long ms){
	struct timespec sleep;
	sleep.tv_sec = 0;
	//since 1ms = 10^6ns
	sleep.tv_nsec = ms* 1000000;
	nanosleep(&sleep, NULL);
}

//draw a pixel with a color
void draw_pixel(int x, int y, color_t color){
	if(x < 0 || y < 0 || x > xlen || y > ylen){
		return;
	}
	unsigned long horizontal = x;
	unsigned long vertical = y * size;
	unsigned short *ptr = (fb_ptr + horizontal + vertical);
	*ptr = color;
}

//draw a rectangle
void draw_rect(int x1, int y1, int width, int height, color_t c){
	int x, y;
	// draw four edges separately
	int i = 0;
	for(i = 0; i <= width; i++){
		draw_pixel(x1++, y1, c);
	}
	for(i = 0; i <= height; i++){
		draw_pixel(x1, y1++, c);
	}
	for(i = 0; i <= width; i++){
		draw_pixel(x1++, y1 + height, c);
	}
	for(i = 0; i <= height; i++){
		draw_pixel(x1 + width, y1++, c);
	}
}

//draw a circle
void draw_circle(int x, int y, int r, color_t color){
	int xx = r;
	int yy = 0;
	int x0 = x;
	int y0 = y;
	int k = 1 - xx;
	while(yy <= xx){
		draw_pixel(xx+x0, yy+y0, color);
		draw_pixel(yy+x0, xx+y0, color);
		draw_pixel(-xx+x0, yy+y0, color);
		draw_pixel(-yy+x0, xx+y0, color);
		draw_pixel(-xx+x0, -yy+y0, color);
		draw_pixel(-yy+x0, -xx+y0, color);
		draw_pixel(xx+x0, -yy+y0, color);
		draw_pixel(yy+x0, -xx+y0, color);
		yy++;
		if(k<=0){
			k = k + 2 * yy + 1;
		} else{
			xx--;
			k = k + 2 * (yy - xx) + 1;
		}
	}
}
