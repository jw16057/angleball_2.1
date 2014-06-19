/*
Author: Jonathan Worobey
Date: 6/2/2014
*/

//SDL includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//STD lib
#include <cmath>
#include <cstdlib>
#include <iostream>//Development only
//Angleball includes
#include "world.h"
#include "ball.h"
#include "Jon_Constants.h"

SDL_Surface *ball_surface;
SDL_Surface *background;
SDL_Surface *screen;

SDL_Event event;

World *w;
int screenWidth;
int screenHeight;

int leftClickXPos;
int leftClickYPos;

bool quit;

double symmetric_round(double x)
{
	if(x > 0)
		return floor(x + 0.5);
	else
		return ceil(x - 0.5);
}

namespace Jon_SDL_functions
{
	SDL_Surface * load_image(char s[], int r, int g, int b)
	{
		SDL_Surface *loadedImage = NULL;
		SDL_Surface *optimizedImage = NULL;

		loadedImage = IMG_Load(s);

		if(loadedImage != NULL)
		{
			optimizedImage = SDL_DisplayFormat(loadedImage);

			SDL_FreeSurface(loadedImage);
			if(optimizedImage != NULL)
			{
				Uint32 colorkey = SDL_MapRGB(optimizedImage->format, r,g,b);
				SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
			}
		}
	
		return optimizedImage;
	}

	SDL_Surface * load_image(char s[])
	{
		SDL_Surface *loadedImage = NULL;
		SDL_Surface *optimizedImage = NULL;

		loadedImage = IMG_Load(s);

		if(loadedImage != NULL)
		{
			optimizedImage = SDL_DisplayFormat(loadedImage);

			SDL_FreeSurface(loadedImage);	
		}
	
		return optimizedImage;
	}

	void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
	{
		SDL_Rect offset;

		offset.x = x;
		offset.y = y;

		SDL_BlitSurface(source, NULL, destination, &offset);
	}

}

bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	screenWidth = info->current_w;
	screenHeight = info->current_h;

	screen = SDL_SetVideoMode(screenWidth, screenHeight, Jon_Constants::SCREEN_BPP, SDL_FULLSCREEN);
	//screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if(screen == NULL)
		return false;

	SDL_WM_SetCaption("Angleball 2.0", NULL);

	return true;
}
bool load_files()
{
	background = Jon_SDL_functions::load_image("background.png");

	return true;
}
void handle_events()
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			leftClickXPos = event.button.x;
			leftClickYPos = event.button.y;
			
			Ball * ptr;
			ptr = new Ball(0, 0, 0, 0, 0, event.button.x, event.button.y);
			w->addTemp(ptr);
		}
		else if(event.button.button == SDL_BUTTON_RIGHT)
		{
			w->deleteBall(event.button.x, event.button.y);
		}
	}
	if(event.type == SDL_MOUSEBUTTONUP)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			int xVel = (leftClickXPos - event.button.x) / 50.0;
			int yVel = (leftClickYPos - event.button.y) / 50.0;

			if(w->deleteTemp())
			{
				Ball * ptr;
				ptr = new Ball(xVel, yVel, 0, 0.01, 0.7, leftClickXPos, leftClickYPos);
				w->addBall(ptr);
			}
		}
	}
	if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_ESCAPE)
			quit = true;
	}
}
void clean_up()
{
	SDL_FreeSurface(ball_surface);
	SDL_Quit();
}
int main(int argc, char *args[])
{
	quit = false;
	leftClickXPos = 0;
	leftClickYPos = 0;

	if(init() == false)
		return 1;
	
	if(load_files() == false)
		return 1;

	Uint32 backgroundColor = SDL_MapRGB(screen->format, 0,150,0);
	w = new World(1, DOWN, screenWidth, screenHeight);

	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			handle_events();

			if(event.type == SDL_QUIT)
				quit = true;
		}

		w->newFrame();

		SDL_FillRect(screen, NULL, backgroundColor);

		w->showSurfaces(screen);

		if(SDL_Flip(screen) == -1)
			return 1;
		
		SDL_Delay(2);
	}

	clean_up();

	return 0;
}