#include<SDL3/SDL.h>

extern SDL_Renderer* rend;

int is_menu_open=0;

int menu_scroll_offset=0;


SDL_Color colors[9] = {
	{0,0,0,0},
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
extern SDL_Color* draw_color;
SDL_FRect convert_rect(SDL_Rect r);

//draw.c
void draw(); 

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
		SDL_FRect frect = convert_rect(rect);
		SDL_RenderRect(rend,&frect);
		rect.x+=1;
		rect.y+=1;
		rect.h-=2;
		rect.w-=2;
	}	
}

void menu_sendclick(SDL_MouseButtonEvent e){
	int ay = e.y-base_color_rect.y;	
	if(ay<0)
		return;
	int ci = ay/(base_color_rect.h+color_y_step);
	if(ci >= 9 || ci < 0) 
		return;
	draw_color=&colors[ci];
	draw();

}

//draw.c
extern SDL_Texture* tile_texture; 

void draw_menu() {
	if(!is_menu_open)
		return;
		
	SDL_SetRenderDrawColor(rend,255,255,255,255);
	SDL_FRect mdraw = convert_rect(menu_region);
	SDL_RenderFillRect(rend,&mdraw);	

	SDL_Rect rect = base_color_rect;
	for(int i=0;i<sizeof(colors)/sizeof(SDL_Color);i++){
		setColor(colors[i]);	
		SDL_FRect frect = convert_rect(rect);
		SDL_RenderTexture(rend,tile_texture,0,&frect);
		SDL_RenderFillRect(rend,&frect); 
		SDL_SetRenderDrawColor(rend,0,0,0,255);
		drawRect(rect,4);
		rect.y+=color_y_step+rect.h;
		
	}	
}

