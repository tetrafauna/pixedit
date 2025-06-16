#include<SDL3/SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<SDL3/SDL_image.h>

typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* texture;
	float size;
	float x_offset;
	float y_offset;
} Canvas;

extern Canvas canvas;

void draw();


extern int do_exit;


//menu.c
extern SDL_Rect menu_region;
extern int is_menu_open;
extern void menu_sendclick(SDL_MouseButtonEvent e);

int is_menu_focus() {
	if(is_menu_open){
		float x,y;
		SDL_GetMouseState(&x,&y);
		SDL_Rect ml = {(int)x,(int)y,1,1};
		if(SDL_HasRectIntersection(&ml,&menu_region))
			return 1;
	}
	return 0;
}

int is_mwheel_down = 0;

//main.c
extern SDL_Color* draw_color;

//draw.c
extern int x_select;
extern int y_select; 

void handle_mm_event(SDL_MouseMotionEvent e){ 
	if(SDL_GetMouseState(0,0) & SDL_BUTTON_MMASK){
		canvas.x_offset+=e.xrel;
		canvas.y_offset+=e.yrel;
		draw();
		return;
	}
	int ax = e.x-canvas.x_offset;
	int ay = e.y-canvas.y_offset;

	if(ax < 0 || ay < 0) {
		x_select=-1;
		y_select=-1;
		draw();
		return;
	}

	y_select = (int) ay / canvas.size;
	x_select = (int) ax / canvas.size;

	draw();
	
}



SDL_Color* get_selected_pixel_pointer() {
	float x,y;
	SDL_GetMouseState(&x,&y);

	int ax = x - canvas.x_offset;
	int ay = y - canvas.y_offset;

	if(ax < 0 || ay < 0)
		return 0;	
	
	int ix = ax/canvas.size;
	int iy = ay/canvas.size;
	return &((SDL_Color*) canvas.pixels->pixels)[iy*canvas.w+ix];
}

void set_selected_pixel(SDL_Color c) {
	SDL_Color* p = get_selected_pixel_pointer();
	if(p)
		*p=c;	
}

SDL_Color get_selected_pixel() {
	SDL_Color* p = get_selected_pixel_pointer();
	if(p)
		return *p;
	return *draw_color;
}

void handle_mb_event(SDL_MouseButtonEvent e) {
	printf("MOUSE BUTTON!\n");
	if(e.button == SDL_BUTTON_MIDDLE){
		if(e.type=SDL_EVENT_MOUSE_BUTTON_DOWN) {
			is_mwheel_down=1;
		} else {
			is_mwheel_down=0;
		}
	}	

	if(e.button == SDL_BUTTON_LEFT) {
		if(is_menu_focus()) { 
			menu_sendclick(e);
		 	return;
		}
		
		set_selected_pixel(*draw_color);
		SDL_DestroyTexture(canvas.texture);
		canvas.texture=0;
		draw(); 
		


	}

}

//menu.c
extern SDL_Rect base_color_rect;

void handle_mw_event(SDL_MouseWheelEvent e) {

	if(is_menu_focus()){
		base_color_rect.y+=e.y*70;	
		draw();
		return;
	}
	
	double dy = (double) e.y / (double) 10;
	printf("%f\n",dy);
	
	int mouse_x;
	int mouse_y;
	float mx,my;
	SDL_GetMouseState(&mx,&my);
	float cx = canvas.x_offset;
	float cy = canvas.y_offset;

	double old_size = canvas.size;
	
	canvas.size*=(double)(1+dy);	
	
	double pixel_delta =(canvas.size-old_size);
	double x_delta = (canvas.size-old_size)*(double) canvas.w;
	double y_delta = (canvas.size-old_size)*(double) canvas.h;
		
	cx-mx*1.1;

	canvas.x_offset+=(cx-mx)*(dy);
	canvas.y_offset+=(cy-my)*(dy);
	draw();
}

//menu.c 
extern int is_menu_open;

//main.c
extern SDL_Window* win;
void resize_canvas(int dx, int dy);
extern char* output_file_name;

//user_input.c
SDL_Color getRGB();

void handle_kb_event(SDL_KeyboardEvent kb) {
	printf("KEY!%d\n",is_menu_open);
	if(kb.type != SDL_EVENT_KEY_DOWN)
		return;
	switch(kb.key){
		case SDLK_M:
			is_menu_open=!is_menu_open;
			goto draw;
		case SDLK_Q:
			do_exit=1;
			break;
		case SDLK_S:
			IMG_SavePNG(canvas.pixels,output_file_name);
			break;
		case SDLK_C:
			*draw_color=getRGB();
			goto draw;
		case SDLK_P:
			*draw_color=get_selected_pixel();
			goto draw;
		case SDLK_DOWN: 
			resize_canvas(0,1);		
			goto draw;
		case SDLK_UP: 
			resize_canvas(0,-1);		
			goto draw;
		case SDLK_RIGHT: 
			resize_canvas(1,0);		
			goto draw;
		case SDLK_LEFT: 
			resize_canvas(-1,0);		
			goto draw;
		draw:	
			draw();
			break;
	}		
}

//main.c 
void on_resize();

void input() {
	SDL_Event e;		
	while(SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_EVENT_QUIT: 
				do_exit=1;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				handle_mm_event(e.motion);
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			case SDL_EVENT_MOUSE_BUTTON_UP:
				handle_mb_event(e.button); 
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				handle_mw_event(e.wheel);
				break;
			case SDL_EVENT_KEY_DOWN:
			case SDL_EVENT_KEY_UP:
				handle_kb_event(e.key);
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				on_resize();
			default:
				printf("Event Type: %d\n",e.type); 

		}
	}
}
