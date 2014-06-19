#ifndef __Jon_SDL_functions_h
#define __Jon_SDL_functions_h

#include "SDL.h"

namespace Jon_SDL_functions
{
	SDL_Surface * load_image(char s[], int r, int g, int b);
	SDL_Surface * load_image(char s[]);
	void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
}

#endif