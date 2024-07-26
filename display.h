#pragma once
#include <SDL.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32


//should this be a singleton ?
typedef struct
{
	uint8_t* pixels; //pixels are either 1 (white) or 0 (black)
	int pixels_count; //DISPLAY_WIDTH * DISPLAY_HEIGHT
} Display;


Display*
Display_create();

//if color is 1 we clear to white, if its 0 we clear to black
void
Display_clear(Display* display, uint8_t color);

void
Display_draw(const Display* display, SDL_Renderer* renderer);

void
Display_destroy(Display* display);