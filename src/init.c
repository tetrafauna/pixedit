#include<SDL3/SDL.h>
#include<SDL3/SDL_image.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

//main.c 
extern SDL_Window* win;
extern SDL_Renderer* rend;
extern int win_width;
extern int win_height;

//user_input.c
extern SDL_Texture* alph;
extern SDL_Texture* color_select_texture;
extern SDL_Surface* color_select_surface;

//draw.c
extern SDL_Texture* tile_texture; 

extern char _binary_textures_alph_png_start[];
extern char _binary_textures_alph_png_end[];

extern char _binary_textures_color_picker_png_start[];
extern char _binary_textures_color_picker_png_end[];

#define _alph_start  _binary_textures_alph_png_start
#define _alph_end    _binary_textures_alph_png_end
#define _alph_len    _alph_end-_alph_start 

#define _color_picker_start  _binary_textures_color_picker_png_start
#define _color_picker_end    _binary_textures_color_picker_png_end
#define _color_picker_len    _color_picker_end-_color_picker_start 

void init(){
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,"Failed to initalize SDL: %s\n",SDL_GetError());
		exit(1);
	}	

	win_width=1280;
	win_height=960;

	win = SDL_CreateWindow("PixelEditor",win_width,win_height,SDL_WINDOW_RESIZABLE);
	if(!win) { 
		fprintf(stderr,"Failed to Create Window: %s\n",SDL_GetError()); 
		exit(1);
	}


	rend = SDL_CreateRenderer(win,0);
	if(!rend) {
		fprintf(stderr,"Failed to Create Renderer: %s",SDL_GetError());
		exit(1);
	}

	SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);

	//TODO embed this using ld
	
	SDL_IOStream* cp_s = SDL_IOFromConstMem(_color_picker_start,_color_picker_len);
	SDL_IOStream* a_s = SDL_IOFromConstMem(_alph_start,_alph_len);
	
	SDL_Surface* ap = IMG_LoadPNG_IO(a_s);
	color_select_surface = IMG_LoadPNG_IO(cp_s);
	
	if(!color_select_surface) {
		fprintf(stderr,"ERROR LOADING TEXTURE: %s",SDL_GetError());
	}
	SDL_Surface* tile_surface = SDL_CreateSurface(2,2,SDL_PIXELFORMAT_RGBA32);
	((int*)tile_surface->pixels)[0]=0xFFAAAAAA;
	((int*)tile_surface->pixels)[1]=0xFF333333;
	((int*)tile_surface->pixels)[2]=0xFF333333;
	((int*)tile_surface->pixels)[3]=0xFFAAAAAA;	

	alph = SDL_CreateTextureFromSurface(rend,ap);
	tile_texture=SDL_CreateTextureFromSurface(rend,tile_surface);
	color_select_texture=SDL_CreateTextureFromSurface(rend,color_select_surface);
	
	SDL_SetTextureScaleMode(tile_texture,SDL_SCALEMODE_NEAREST);
	SDL_SetTextureScaleMode(alph,SDL_SCALEMODE_NEAREST);
	SDL_SetTextureScaleMode(color_select_texture,SDL_SCALEMODE_NEAREST);

	SDL_DestroySurface(tile_surface);
	SDL_DestroySurface(ap);
	
	SDL_SetRenderDrawColor(rend,255,0,0,255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

}

void uninit(){
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

