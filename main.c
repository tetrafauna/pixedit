#include<SDL2/SDL.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

SDL_Window* win;
SDL_Renderer* rend;

int do_exit = 0;


//init.c
void init();
void uninit();

//input.c
void input();

//menu.c
void resize_menu();
void draw_menu();

typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* texture;
	double size;
	int x_offset;
	int y_offset;
} Canvas; 

int win_width;
int win_height;

SDL_Color draw_color = {255,0,0,255};

Canvas canvas;

Canvas create_canvas(int x, int y) {
	Canvas retv={x,y,
		SDL_CreateRGBSurface(0,x,y,32,0xFF000000,0x00FF0000,0x0000FF00,0x000000FF),
		0,60,-100,-50
	};
	
	memset(retv.pixels->pixels,122,x*y*4);
	for(int i=0;i<x*y;i++)
		((int*)retv.pixels->pixels)[i]=rand();
	
	return retv;
}


void on_resize() {
	SDL_GetRendererOutputSize(rend,&win_width,&win_height);
	resize_menu(); 
}

//draw.c
void draw();

int main(int argc, char** argv){
	srand(time(0));	
	int x = 16;
	int y = 16;

	if(argc > 1){
		x = atoi(argv[1]);
		y = atoi(argv[2]);
	}

	init();
	on_resize();
	canvas = create_canvas(x,y);
	draw();
	while(!do_exit){
		input();
		usleep(1000);
	}
	uninit();
}
