#include<SDL2/SDL.h>

extern SDL_Renderer* rend;

int is_menu_open=0;

int menu_scroll_offset=0;


SDL_Color colors[8] = {
	{255, 0,   0,   255},
	{0,   255, 0,   255},
	{0,   0,   255, 255},
	{0,   255, 255, 255},
	{255, 0,   255, 255},
	{255, 255, 0,   255},
	{255, 255, 255, 255},
	{0,   0,   0,   255},
		
};

SDL_Rect menu_region;

int color_y_step = 5;
SDL_Rect base_color_rect={0,5,0,0};

//main.c
void setColor(SDL_Color c);
extern int win_width,win_height;

void resize_menu(){
	menu_region.x=0;
	menu_region.y=0;
	menu_region.h = win_height; 
	menu_region.w = win_width/5;
	base_color_rect.x=menu_region.w/10;
	base_color_rect.w=8*menu_region.w/10;
	base_color_rect.h=base_color_rect.w; 
} 

void drawRect(SDL_Rect rect, int bw) {
	for(int i=0;i<bw;i++){
		SDL_RenderDrawRect(rend,&rect);
		rect.x+=1;
		rect.y+=1;
		rect.h-=2;
		rect.w-=2;
	}	
}

void menu_sendclick(int x, int y){
	
}

void draw_menu() {
	if(!is_menu_open)
		return;
	
	SDL_SetRenderDrawColor(rend,255,255,255,255);
	SDL_RenderFillRect(rend,&menu_region);	

	SDL_Rect rect = base_color_rect;
	for(int i=0;i<sizeof(colors)/sizeof(SDL_Color);i++){
		setColor(colors[i]);	
		SDL_RenderFillRect(rend,&rect); 
		SDL_SetRenderDrawColor(rend,0,0,0,200);
		drawRect(rect,4);
		rect.y+=color_y_step+rect.h;
		
	}
	
}

