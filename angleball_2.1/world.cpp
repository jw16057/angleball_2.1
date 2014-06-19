#include "World.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Jon_Constants.h"
#include "Jon_SDL_functions.h"
#include <ctime>

World::World(int numberOfBalls_, Direction gravityDirection_, int screenWidth_, int screenHeight_, double gravityStrength_)
{
	tempOnTop = false;
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
	srand((int) time(0));
	for(int x = numberOfBalls_; x > 0; x--)
	{
		balls.push_back(Ball(0, 0, 0, 0.01, 0.7, 0, screenHeight));
		balls.back().bounce();
		//balls.push_back(Ball(rand()%20, rand()%-5, 0, 0.01, 0.7, DEFAULT_X_POSITION, DEFAULT_Y_POSITION));
		
	}
}
void World::newFrame() // Call this to advance the world one tick
{
	for(int x = balls.size()-1; x >= 0; x--)
	{
		balls[x].tick(screenWidth, screenHeight);
		if(balls[x].isStill())
			balls.erase(balls.begin()+x);
	}
}
void World::addBall(Ball * x)
{
	balls.push_back(*x);
}
void World::addTemp(Ball * x)
{
	if(!tempOnTop)
	{
		balls.push_back(*x);
		tempOnTop = true;
	}
}
bool World::deleteTemp()
{
	if(tempOnTop)
	{
		balls.pop_back();
		tempOnTop = false;
		return true;
	}
	else
		return false;
}
bool World::deleteBall(int MouseX, int MouseY)
{
	return true;
}
Ball & World::getBall(int x)
{
	if(x < 0 || x >= (int) balls.size())
		exit(3);
	return balls[x];
}
void World::showSurfaces(SDL_Surface * s)
{
	for(int x = 0; x < getNumberOfBalls(); x++)
	{
		Jon_SDL_functions::apply_surface((int) floor(balls[x].getX()), (int) ceil(balls[x].getY()), balls[x].getFace(), s);
	}
}