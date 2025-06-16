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

//draw.c
extern SDL_Texture* tile_texture; 

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

	//TODO embed this using ld
	SDL_Surface* ap = IMG_Load("./textures/alph.png");
	alph = SDL_CreateTextureFromSurface(rend,ap);
	SDL_DestroySurface(ap);
	SDL_Surface* tile_surface = SDL_CreateSurface(2,2,SDL_PIXELFORMAT_RGBA32);
	((int*)tile_surface->pixels)[0]=0xAAAAAAFF;
	((int*)tile_surface->pixels)[1]=0x333333FF;
	((int*)tile_surface->pixels)[3]=0x333333FF;
	((int*)tile_surface->pixels)[4]=0xAAAAAAFF;
	tile_texture=SDL_CreateTextureFromSurface(rend,tile_surface);
	SDL_SetTextureScaleMode(tile_texture,SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(tile_surface);
	
	SDL_SetRenderDrawColor(rend,255,0,0,255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

}

void uninit(){
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

