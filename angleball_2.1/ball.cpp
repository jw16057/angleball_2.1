#ifndef __ball_cpp
#define __ball_cpp
#include "ball.h"
#include "Jon_Constants.h"
#include "Jon_SDL_functions.h"

double symmetric_round(double);

Ball::Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping_, double x_, double y_)
{
	radius = 16;
	lastMovement = 0;
	p.x = x_;
	p.y = y_ - (radius * 2);

	historyPos.push_back(Pos(p.x, p.y));

	xVel = xVel_;
	yVel = yVel_;
	xAccel = xAccel_;
	yAccel = yAccel_;
	damping = damping_;

	face = Jon_SDL_functions::load_image("ball.png", 0, 0, 0);

	if(face == NULL)
		exit(3);
}

void Ball::tick(int screenWidth, int screenHeight)
{
	p.x += xVel;
	p.y += yVel;

	xVel += xAccel;
	yVel += yAccel;
	

	if(p.y > screenHeight-radius*2)
	{
		int displacement = (int) p.y - (screenHeight-radius*2);
		p.y = (screenHeight-radius*2) - displacement;
		yVel = -yVel * damping;
		xVel = xVel * damping;
	}
	if(p.x > screenWidth-radius*2)
	{
		int displacement = (int) p.x - (screenWidth-radius*2);
		p.x = (screenWidth-radius*2) - displacement;
		yVel = yVel * damping;
		xVel = -xVel * damping;
		
	}
	if(p.x < 0)
	{
		p.x = -p.x;
		yVel = yVel * damping;
		xVel = -xVel * damping;
	}

	Pos current(p.x, p.y);

	if(current == historyPos.back())
		lastMovement++;
	else
		lastMovement = 0;

	historyPos.push_back(current);
}

bool Ball::isStill()
{
	return false; ////////////////////////////////////////NOTICE
	if(lastMovement > 10)
		return true;
	else
		return false;
}

void Ball::bounce()
{
	xVel = rand()%5;
	yVel = rand()%5;
	if(rand() < RAND_MAX/2)
		xVel = -xVel;
	//if(rand() < RAND_MAX/2)
		yVel = -yVel;
}

#endif