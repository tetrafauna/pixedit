#include<stdio.h>
#include<SDL3/SDL.h>

//main.c
extern SDL_Renderer* rend;
extern SDL_Window* win;
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
		unsigned int num = e.key.key -'0';
		if(!(num<=max))
			continue;
		return num;
	}
}

SDL_Color getRGB() {
	
	SDL_Color retv = {0,0,0,0};

	SDL_FRect draw_rect = { 
		10,10,color_select_surface->w*scale,color_select_surface->h*scale
	};
	SDL_FRect src_rect  ={
		0,0,6,7
	};
	SDL_RenderTexture(rend,color_select_texture,0,&draw_rect);
	SDL_RenderPresent(rend);

	draw_rect.x+=2*scale;
	draw_rect.y+=11*scale;
	draw_rect.w=6*scale;
	draw_rect.h=7*scale;
	
	for(int i=0;i<4;i++) {

		int x = get_num(2);
		if(x == -1)
			goto quit;
		src_rect.x=(26+x)*6; 
		SDL_RenderTexture(rend,alph,&src_rect,&draw_rect);
		SDL_RenderPresent(rend);
		((unsigned char*)&retv)[i]+=x*100;
		
		draw_rect.x+=7*scale;	
		int y;
		if(x != 2)	
			y = get_num(9);
		else
			y = get_num(5);
		if(y == -1)
			goto quit;
		src_rect.x=(26+y)*6; 
		SDL_RenderTexture(rend,alph,&src_rect,&draw_rect);
		SDL_RenderPresent(rend);
		((unsigned char*)&retv)[i]+=y*10;
		
		draw_rect.x+=7*scale;	
		if(x != 2)	
			y = get_num(9);
		else
			y = get_num(5);
		if(y == -1)
			goto quit;
		src_rect.x=(26+y)*6; 
		SDL_RenderTexture(rend,alph,&src_rect,&draw_rect);
		SDL_RenderPresent(rend);
		((unsigned char*)&retv)[i]+=y*1;
		draw_rect.x+=11*scale;
	}
	

	printf("%d:%d:%d:%d\n",retv.r,retv.g,retv.b,retv.a);
	SDL_Delay(100);

	return retv;

	quit:
	return *draw_color;
}




