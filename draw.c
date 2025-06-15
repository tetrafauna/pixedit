#include<SDL2/SDL.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>



typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* texture;
	double size;
	int x_offset;
	int y_offset;
} Canvas; 

//menu.c
void draw_menu();

//main.c
extern int win_width;
extern int win_height;
extern SDL_Color draw_color;
extern Canvas canvas;
extern SDL_Window* win;
extern SDL_Renderer* rend;

void setColor(SDL_Color c) {
	SDL_SetRenderDrawColor(rend,c.r,c.g,c.b,c.a);
}

void draw_canvas() {
	SDL_Rect draw_rect = {
		canvas.x_offset,canvas.y_offset,(int)(canvas.size*canvas.w),(int)(canvas.size*canvas.h)
	};

	if(!canvas.texture) {
		canvas.texture=SDL_CreateTextureFromSurface(rend,canvas.pixels); 
	}	
	SDL_RenderCopy(rend,canvas.texture,0,&draw_rect);
}

void draw_paint_color() {
	SDL_Rect rect = {win_width-25,win_height-25,20,20};	
	setColor(draw_color);
	SDL_RenderFillRect(rend,&rect);
}

void draw(){
	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);
	draw_canvas(); 
	draw_menu();
	draw_paint_color();
	SDL_RenderPresent(rend);	
}
