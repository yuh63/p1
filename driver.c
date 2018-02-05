/**
 * Yue Hao
 * yuh63@pitt.edu
 * 2/4/2018
 * CS1550
 */
 
#include <stdio.h>

typedef unsigned short color_t;

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
	getkey();
	sleep_ms(3000);
	draw_pixel(200,300,0xFFFFFF);
	draw_pixel(0,-150,0x0000FF);
	draw_rect(0,0,240,360,0xF69679);
	draw_circle(-100,150,100,0x91268F);
	sleep_ms(10000);
	clear_screen();
	exit_graphics();
	return 0;
}
