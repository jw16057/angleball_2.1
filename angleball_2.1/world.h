#ifndef __world_h
#define __world_h
#include <vector>
#include "ball.h"

enum Direction {UP, DOWN, LEFT, RIGHT};

class World{
public:
	World(int numberOfBalls_, Direction gravityDirection_, int screenWidth_, int screenHeight, double gravityStrength_ = 0.01);
	void newFrame(); // Call this to advance the world one tick
	void addBall(Ball * x);
	void deleteBall(int MouseX_, int MouseY_);

	Direction getGravityDirection() {return gravityDirection;}
	double getGravityStrength() {return gravityStrength;}
	int getNumberOfBalls() {return balls.size();}
	Ball & getBall(int x);
private:
	int screenWidth;
	int screenHeight;
	long frameNum;

	Direction gravityDirection;
	double gravityStrength;

	std::vector <Ball> balls;
};

#endif
