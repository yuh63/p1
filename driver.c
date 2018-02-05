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
	sleep_ms(3000);
	draw_pixel(200,300,10);
	draw_pixel(0,150,20);
	draw_rect(0,0,240,360,30);
	draw_circle(200,250,100,40);
	sleep_ms(3000);
	clear_screen();
	exit_graphics();
	return 0;
}
