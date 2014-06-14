#include "World.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <ctime>

World::World(int numberOfBalls_, Direction gravityDirection_, double gravityStrength_)
{
	srand(time(0));
	for(int x = numberOfBalls_; x > 0; x--)
	{
		balls.push_back(Ball(0, 0, 0, 0.01, 0.7, DEFAULT_X_POSITION, DEFAULT_Y_POSITION));
		balls.back().bounce();
		//balls.push_back(Ball(rand()%20, rand()%-5, 0, 0.01, 0.7, DEFAULT_X_POSITION, DEFAULT_Y_POSITION));
		
	}
}
void World::newFrame() // Call this to advance the world one tick
{
	for(int x = balls.size()-1; x >= 0; x--)
	{
		if(balls[x].isStill())
			balls.erase(balls.begin()+x);
		else
			balls[x].tick();
	}
}
void World::addBall(Ball * x)
{
	balls.push_back(*x);
}
void World::deleteBall(int MouseX, int MouseY)
{
}
Ball & World::getBall(int x)
{
	if(x < 0 || x >= balls.size())
		exit(3);
	return balls[x];
}