#include<SDL3/SDL.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>



typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* texture;
	float size;
	float x_offset;
	float y_offset;
} Canvas; 

//menu.c
void draw_menu();

//main.c
extern int win_width;
extern int win_height;
extern SDL_Color* draw_color;
extern Canvas canvas;
extern SDL_Window* win;
extern SDL_Renderer* rend;

//input.c
extern int brush_size;

//pixels.c
SDL_Rect get_selected_pixels();

int x_select=-1;
int y_select=-1;

SDL_Texture* tile_texture;

void setColor(SDL_Color c) {
	SDL_SetRenderDrawColor(rend,c.r,c.g,c.b,c.a);
}

void draw_canvas() {
	SDL_FRect draw_rect;
	draw_rect.x=canvas.x_offset;
	draw_rect.y=canvas.y_offset;
	draw_rect.w=canvas.size*canvas.w;
	draw_rect.h=canvas.size*canvas.h;

	if(!canvas.texture) {
		canvas.texture=SDL_CreateTextureFromSurface(rend,canvas.pixels); 
		SDL_SetTextureScaleMode(canvas.texture,SDL_SCALEMODE_NEAREST);
	}
	SDL_RenderTextureTiled(rend,tile_texture,0,canvas.size/4,&draw_rect);
	SDL_RenderTexture(rend,canvas.texture,0,&draw_rect);

	if(x_select >= 0 && x_select < canvas.w && y_select >= 0 && y_select < canvas.h){
		SDL_SetRenderDrawColor(rend,255,255,255,255);
		SDL_Rect rect = get_selected_pixels();
		draw_rect.x =canvas.x_offset+rect.x*canvas.size;
		draw_rect.y =canvas.y_offset+rect.y*canvas.size;
		draw_rect.w =canvas.size*rect.w;
		draw_rect.h =canvas.size*rect.h;
		SDL_RenderRect(rend,&draw_rect);
	}	
}

void draw_paint_color() {
	SDL_FRect rect = {(float)win_width-25,(float)win_height-25,(float)20,(float)20};	
	setColor(*draw_color);
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
