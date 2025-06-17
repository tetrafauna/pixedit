#include<stdio.h>
#include<SDL3/SDL.h>

//main.c
extern SDL_Renderer* rend;
extern SDL_Window* win;
extern int win_height;
extern int win_width;
extern int do_exit;
extern SDL_Color* draw_color;

SDL_Texture* alph;
SDL_Texture* color_select_texture;
SDL_Surface* color_select_surface;

float scale = 10;

int get_num(int max){
	SDL_Event e;
	while(1){
		SDL_PollEvent(&e);
		if(e.type==SDL_EVENT_QUIT)
			return -1;
		if(e.type!=SDL_EVENT_KEY_DOWN)
			continue;
		if(e.key.key == SDLK_Q || e.key.key == SDLK_ESCAPE)
			return -1;
		if(e.key.key == SDLK_BACKSPACE)
			return -2;
		unsigned int num = e.key.key -'0';
		if(!(num<=max))
			continue;
		return num;
	}
}

SDL_Color getRGB() {


	SDL_Color retv = {0,0,0,0};	

	scale=((float)win_width-40)/(float)color_select_surface->w;

	SDL_FRect draw_rect = { 
		20,20,color_select_surface->w*scale,color_select_surface->h*scale
	};
	
	SDL_FRect src_rect  ={
		0,0,6,7
	};
	
	SDL_Texture* ttex = SDL_CreateTexture(rend,SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_TARGET,
			color_select_surface->w,
			color_select_surface->h);
	SDL_SetTextureScaleMode(ttex,SDL_SCALEMODE_NEAREST);
	
	SDL_SetRenderTarget(rend,ttex);
		
	SDL_RenderTexture(rend,color_select_texture,0,0);
	SDL_RenderPresent(rend);
	
	SDL_SetRenderTarget(rend,0);
	SDL_RenderTexture(rend,ttex,0,&draw_rect);
	SDL_RenderPresent(rend);

	SDL_FRect rect; 	
	rect.x=2;
	rect.y=11;
	rect.w=6;
	rect.h=7;
	
	for(int i=0;i<4;i++){
		
		rect.x=3+i*25;
		
		int max = 2;

		SDL_SetRenderTarget(rend,ttex);
		
		SDL_SetRenderDrawColor(rend,255,255,255,255);
		SDL_RenderFillRect(rend,&rect);
		rect.x+=7;
		SDL_RenderFillRect(rend,&rect);
		rect.x+=7;
		SDL_RenderFillRect(rend,&rect);
		SDL_RenderPresent(rend);
		SDL_SetRenderTarget(rend,0);
		SDL_RenderTexture(rend,ttex,0,&draw_rect);
		SDL_RenderPresent(rend);
	
		SDL_SetRenderTarget(rend,ttex);
		
		rect.x=2+i*25;
		//fist numer
		int x = get_num(max);
		max=9;
		if(x == 2)
			max=5;
		if(x == -1)
			goto quit;
		if(x == -2){
			if(i)i--;
			i--;
			continue;
		}
		src_rect.x=(26+x)*6; 
		SDL_RenderTexture(rend,alph,&src_rect,&rect);
		SDL_RenderPresent(rend);
		((unsigned char*)&retv)[i]+=x*100;
		rect.x+=7;

		SDL_SetRenderTarget(rend,0);
		SDL_RenderTexture(rend,ttex,0,&draw_rect);
		SDL_RenderPresent(rend);
		
	
		//second numer 
		SDL_SetRenderTarget(rend,ttex);
		
		x = get_num(max);
		if(x == -1)
			goto quit;
		if(x == -2){
			if(i)i--;
			i--;
			continue;
		}
		
		src_rect.x=(26+x)*6; 
		SDL_RenderTexture(rend,alph,&src_rect,&rect);
		SDL_RenderPresent(rend);
		((unsigned char*)&retv)[i]+=x*10;
		rect.x+=7;
			
		SDL_SetRenderTarget(rend,0);
		SDL_RenderTexture(rend,ttex,0,&draw_rect);
		SDL_RenderPresent(rend);
		//third numer
		SDL_SetRenderTarget(rend,ttex);
		
		x = get_num(max);
		if(x == -1)
			goto quit;
		if(x == -2){
			if(i)i--;
			i--;
			continue;
		}
		
		src_rect.x=(26+x)*6; 
		SDL_RenderTexture(rend,alph,&src_rect,&rect);
		SDL_RenderPresent(rend);
		((unsigned char*)&retv)[i]+=x;
			
		SDL_SetRenderTarget(rend,0);
		SDL_RenderTexture(rend,ttex,0,&draw_rect);
		SDL_RenderPresent(rend);

	}	
	
	SDL_SetRenderTarget(rend,0);
	SDL_RenderTexture(rend,ttex,0,&draw_rect);
	SDL_RenderPresent(rend);
	SDL_DestroyTexture(ttex);
	
	return retv;

	SDL_Delay(100);

	return retv;

	quit:
	SDL_SetRenderTarget(rend,0);
	SDL_DestroyTexture(ttex);
	return *draw_color;
}




