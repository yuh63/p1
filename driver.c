/**
 * Yue Hao
 * yuh63@pitt.edu
 * 2/4/2018
 * CS1550
 */
 
#include "library.c"

typedef unsigned short color_t;
#define colorform(r,g,b) ((color_t) (r << 11)|(g << 5)|(b))

void init_graphics();
void exit_graphics();
void clear_screen();
char getkey();
void sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void draw_circle(int x, int y, int r, color_t color);

int main(int argc, char** argv){
	// a sample program to show functions
	init_graphics();
	clear_screen();
	sleep_ms(3000);
	//draw_pixel(200,300,colorform(0,50,0));
	//draw_pixel(0,150,colorform(20,0,20));
	//draw_rect(0,0,240,360,colorform(30,0,0));
	//draw_circle(200,250,100,colorform(0,0,30));
	sleep_ms(3000);
	clear_screen();
	exit_graphics();
	return 0;
}
