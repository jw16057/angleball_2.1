/*
Author: Jonathan Worobey
Date: 6/2/2014
*/

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "ball.h"
#include <cmath>
#include <cstdlib>
#include <iostream>//Development only
using namespace std;

SDL_Surface *ball_surface;
SDL_Surface *background;
SDL_Surface *screen;

SDL_Event event;

double symmetric_round(double x)
{
	if(x > 0)
		return floor(x + 0.5);
	else
		return ceil(x - 0.5);
}
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
bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if(screen == NULL)
		return false;

	SDL_WM_SetCaption("Angleball 2.0", NULL);

	return true;
}
bool load_files()
{
	ball_surface = load_image("ball.png", 0, 0, 0);
	background = load_image("background.png");

	if(ball_surface == NULL)
		return false;

	return true;
}
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}
void clean_up()
{
	SDL_FreeSurface(ball_surface);
	SDL_Quit();
}
int main(int argc, char *args[])
{
	bool quit = false;

	if(init() == false)
		return 1;
	
	if(load_files() == false)
		return 1;

	Ball *ball1;
	ball1 =  new Ball(20, -5, 0, 0.01, 0.7, DEFAULT_X_POSITION, DEFAULT_Y_POSITION);
	int tick = 0;
	int preX;
	int preY;

	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quit = true;
		}
		preX = (int) symmetric_round(ball1->x);
		preY = (int) symmetric_round(ball1->y);

		ball1->tick();

		if(preX == symmetric_round(ball1->x) && preY == symmetric_round(ball1->y))
			tick++;
		else
			tick = 0;
		
		if(tick >= 5)
		{
			delete ball1;
			ball1 = new Ball(rand() % 50,-1 * (rand() % 10),0,0.01, 0.7, preX, preY);
			tick = 0;
			SDL_Delay(100);
		}

		apply_surface(0,0,background,screen);
		apply_surface((int) floor(ball1->x), (int) ceil(ball1->y), ball_surface, screen);

		if(SDL_Flip(screen) == -1)
			return 1;
		
		SDL_Delay(2);
	}
	std::cout << tick << "\n";

	clean_up();

	return 0;
}