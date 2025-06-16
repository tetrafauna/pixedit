#include<SDL3/SDL.h>
#include<SDL3/SDL_image.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

SDL_Window* win;
SDL_Renderer* rend;

int do_exit = 0;


//init.c
void init();
void uninit();

//input.c
void input();

//menu.c
void resize_menu();
void draw_menu();

//draw.c
void draw();

typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* texture;
	double size;
	int x_offset;
	int y_offset;
} Canvas; 

int win_width;
int win_height;

SDL_Color draw_color = {255,0,0,255};
char* output_file_name = "out.png";

Canvas canvas = {0};

SDL_FRect convert_rect(SDL_Rect r){
	return (SDL_FRect) {(float)r.x,(float)r.y,(float)r.w,(float)r.h};	
}

Canvas create_canvas(int x, int y) {
	Canvas retv={x,y,
		SDL_CreateSurface(x,y,SDL_PIXELFORMAT_RGBA32),
		0,60,0,0
	};
	
	for(int i=0;i<x*y;i++){
		((unsigned int*)retv.pixels->pixels)[i]=0xFF0000FF;
	}
	return retv;
}

void load_png(char* path){
	if(canvas.texture)
		SDL_DestroyTexture(canvas.texture);	
	if(canvas.pixels)
		SDL_DestroySurface(canvas.pixels); 
	
	//TODO change format
	canvas.pixels=IMG_Load(path);
	canvas.w=canvas.pixels->w;
	canvas.h=canvas.pixels->h;
	//canvas.texture = SDL_CreateTextureFromSurface(rend,canvas.pixels);
	canvas.size=60;
	canvas.x_offset=0;
	canvas.y_offset=0;

	draw();	
	output_file_name=path;
	
}

void resize_canvas(int dx,int dy) {

	if(canvas.w+dx <= 0 || canvas.h+dy <=0)
		return;

	Canvas new_canvas = create_canvas(canvas.w+dx,canvas.h+dy);
	
	new_canvas.size=canvas.size;
	new_canvas.x_offset=canvas.x_offset;
	new_canvas.y_offset=canvas.y_offset;

	int copy_x_size = canvas.w;
	if(dx<0)
		copy_x_size = new_canvas.w;
	int copy_y_size = canvas.h;
	if(dy<0)
		copy_y_size = new_canvas.h;


	for(int y=0;y<copy_y_size;y++){
		for(int x=0;x<copy_x_size;x++){
			int pixel = ((int*)canvas.pixels->pixels)[y*canvas.w+x];
			((int*)new_canvas.pixels->pixels)[y*new_canvas.w+x] = pixel;
		}
	}
	if(canvas.texture)
		SDL_DestroyTexture(canvas.texture);
	SDL_DestroySurface(canvas.pixels);

	canvas=new_canvas;
}

void on_resize() {
	SDL_GetCurrentRenderOutputSize(rend,&win_width,&win_height);
	resize_menu(); 
}


int main(int argc, char** argv){

	init();
	on_resize();
	
	if(argc == 1)
		canvas = create_canvas(16,16);
	else if (argc == 2)
		load_png(argv[1]);
	else if (argc == 3)
		canvas = create_canvas(atoi(argv[1]),atoi(argv[2]));
	
	draw();
	while(!do_exit){
		input();
		usleep(1000);
	}
	uninit();
}
