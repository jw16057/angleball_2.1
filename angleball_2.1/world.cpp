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
		
		balls.push_back(Ball(rand()%20, rand()%-5, 0, 0.01, 0.7, DEFAULT_X_POSITION, DEFAULT_Y_POSITION));
	}
}
void World::newFrame() // Call this to advance the world one tick
{
	for(int x = 0; x < balls.size(); x++)
	{
		balls[x].tick();
	}
}
void World::addBall(Ball x)
{

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