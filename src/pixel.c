#include<SDL3/SDL.h>
#include "canvas.h"
#include<math.h>

extern int brush_size;

extern Canvas canvas;

SDL_Rect get_selected_pixels() {
	float x,y;
	SDL_GetMouseState(&x,&y); 

	float ax = x-canvas.x_offset;
	float ay = y-canvas.y_offset;
	
	float bs = (float) brush_size;

	int ix = (ax/canvas.size) - (bs-1.0)/2.0;
	int iy = (ay/canvas.size) - (bs-1.0)/2.0;

	return (SDL_Rect) {ix,iy,brush_size,brush_size};
}


