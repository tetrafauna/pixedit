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

int x_select=-1;
int y_select=-1;

SDL_Texture* tile_texture;

void setColor(SDL_Color c) {
	SDL_SetRenderDrawColor(rend,c.r,c.g,c.b,c.a);
}

void draw_canvas() {
	SDL_FRect draw_rect = {
		(float) canvas.x_offset,(float)canvas.y_offset,(float)(canvas.size*canvas.w),(float)(canvas.size*canvas.h)
	};

	if(!canvas.texture) {
		canvas.texture=SDL_CreateTextureFromSurface(rend,canvas.pixels); 
		SDL_SetTextureScaleMode(canvas.texture,SDL_SCALEMODE_NEAREST);
	}
	SDL_RenderTexture(rend,canvas.texture,0,&draw_rect);

	if(x_select >= 0 && x_select < canvas.w && y_select >= 0 && y_select < canvas.h){
		SDL_SetRenderDrawColor(rend,255,255,255,255);
		draw_rect.x =(float) (canvas.x_offset+x_select*canvas.size);
		draw_rect.y =(float) (canvas.y_offset+y_select*canvas.size);
		draw_rect.w =(float) (canvas.size);
		draw_rect.h =(float) (canvas.size);
		SDL_RenderRect(rend,&draw_rect);
	}	
}

void draw_paint_color() {
	SDL_FRect rect = {(float)win_width-25,(float)win_height-25,(float)20,(float)20};	
	setColor(draw_color);
	SDL_RenderFillRect(rend,&rect);
}

void draw(){
	SDL_SetRenderDrawColor(rend,0,0,0,255);
	SDL_RenderClear(rend);
	SDL_RenderTextureTiled(rend,tile_texture,0,canvas.size/4,0);
	draw_canvas(); 
	draw_menu();
	draw_paint_color();
	SDL_RenderPresent(rend);	
}
