#include<SDL2/SDL.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* pixels_cache;
	double size;
	int x_offset;
	int y_offset;
} Canvas;

extern Canvas canvas;

void draw();


extern int do_exit;


//menu.c
extern SDL_Rect menu_region;
extern int is_menu_open;

int is_menu_focus() {
	if(is_menu_open){
		SDL_Rect ml = {0,0,1,1};
		SDL_GetMouseState(&ml.x,&ml.y);
		if(SDL_HasIntersection(&ml,&menu_region))
			return 1;
	}
	return 0;
}

int is_mwheel_down = 0;

void handle_mm_event(SDL_MouseMotionEvent e){ 
	if(SDL_GetMouseState(0,0) & SDL_BUTTON_MMASK){
		canvas.x_offset+=e.xrel;
		canvas.y_offset+=e.yrel;
	}
	draw();
}

void handle_mb_event(SDL_MouseButtonEvent e) {
	printf("MOUSE BUTTON!\n");
	if(e.button == SDL_BUTTON_MIDDLE){
		if(e.type=SDL_MOUSEBUTTONDOWN) {
			is_mwheel_down=1;
		} else {
			is_mwheel_down=0;
		}
	}	

	if(e.button == SDL_BUTTON_LEFT) {
		if(is_menu_focus()) {

		}
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
	SDL_GetMouseState(&mouse_x,&mouse_y);
	double cx = canvas.x_offset;
	double cy = canvas.y_offset;
	double mx = (double) mouse_x;
	double my = (double) mouse_y;

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

extern int is_menu_open;

void handle_kb_event(SDL_KeyboardEvent kb) {
	printf("KEY!%d\n",is_menu_open);
	if(kb.type != SDL_KEYDOWN)
		return;
	switch(kb.keysym.sym){
		case SDLK_m:
			is_menu_open=!is_menu_open;
			draw();
			break; 
		case SDLK_q:
			do_exit=1;
			break;

	}		
}

//main.c 
void on_resize();

void input() {
	SDL_Event e;		
	while(SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT: 
				do_exit=1;
				break;
			case SDL_MOUSEMOTION:
				handle_mm_event(e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handle_mb_event(e.button); 
				break;
			case SDL_MOUSEWHEEL:
				handle_mw_event(e.wheel);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handle_kb_event(e.key);
				break;
			case SDL_WINDOWEVENT:
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					on_resize();
			default:
				printf("Event Type: %d\n",e.type); 

		}
	}
}
