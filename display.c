#include "main.h"
#include "display.h"


Display*
Display_create()
{
	Display* display = malloc(sizeof(Display));
	if (display != NULL)
	{
		display->pixels_count = (DISPLAY_WIDTH) * (DISPLAY_HEIGHT);

		display->pixels = malloc(display->pixels_count * sizeof(uint8_t));
	}
	return display;
}

void
Display_clear(Display* display, uint8_t color)
{
	for (int i = 0; i < display->pixels_count; i++)
	{
		display->pixels[i] = color;
	}
}

void
Display_draw(const Display* display, SDL_Renderer* renderer)
{
	int pixel_width = WINDOW_WIDTH / DISPLAY_WIDTH;
	int pixel_height = WINDOW_HEIGHT / DISPLAY_HEIGHT;

	
	for (int i = 0; i < DISPLAY_HEIGHT; i++)
	{
		for (int j = 0; j < DISPLAY_WIDTH; j++)
		{
			int x = j * pixel_width;
			int y = i * pixel_height;

			SDL_Rect rect =
			{
				x, y,
				pixel_width, pixel_height
			};

			int pixel_index = j + (DISPLAY_WIDTH * i);
			uint8_t pixel = display->pixels[pixel_index];

			if (pixel == 1)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else if (pixel == 0)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void
Display_destroy(Display* display)
{
	if (display)
	{
		free(display->pixels);
		display->pixels = NULL;

		free(display);
		display = NULL;
	}
}