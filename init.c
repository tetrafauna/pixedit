#include<SDL2/SDL.h>
#include<stdlib.h>
#include<unistd.h>

extern SDL_Window* win;
extern SDL_Renderer* rend;

extern int win_width;
extern int win_height;


void init(){
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,"Failed to initalize SDL: %s\n",SDL_GetError());
		exit(1);
	}
	
	win_width=1280;
	win_height=960;

	win = SDL_CreateWindow("Strategy Game 1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			win_width,win_height,SDL_WINDOW_RESIZABLE);
	if(!win) { 
		fprintf(stderr,"Failed to Create Window: %s\n",SDL_GetError()); 
		exit(1);
	}

	rend = SDL_CreateRenderer(win,-1,0);
	if(!rend) {
		fprintf(stderr,"Failed to Create Renderer: %s",SDL_GetError());
		exit(1);
	}
	
	SDL_SetRenderDrawColor(rend,255,0,0,255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

}

void uninit(){
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

