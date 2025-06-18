#pragma once
#include<SDL3/SDL.h>

typedef struct {
	int w;
	int h;
	SDL_Surface* pixels;
	SDL_Texture* texture;
	float size;
	float x_offset;
	float y_offset;
} Canvas; 

