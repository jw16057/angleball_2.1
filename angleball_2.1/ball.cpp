#ifndef __ball_cpp
#define __ball_cpp
#include "ball.h"

double symmetric_round(double);

Ball::Ball()
{
	radius = DEFAULT_BALL_RADIUS;
	damping = DEFAULT_DAMPING;
	lastMovement = 0;

	p.x = 0;
	p.y = SCREEN_HEIGHT - (radius * 2);

	historyPos.push_back(Pos(p.x, p.y));

	xVel = 0;
	yVel = 0;

	xAccel = 0;
	yAccel = 0;
}

Ball::Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping_, double x_, double y_)
{
	radius = DEFAULT_BALL_RADIUS;
	lastMovement = 0;
	p.x = x_;
	p.y = y_;

	historyPos.push_back(Pos(p.x, p.y));

	xVel = xVel_;
	yVel = yVel_;
	xAccel = xAccel_;
	yAccel = yAccel_;
	damping = damping_;
}

void Ball::tick()
{
	p.x += xVel;
	p.y += yVel;

	xVel += xAccel;
	yVel += yAccel;
	

	if(p.y > SCREEN_HEIGHT-radius*2)
	{
		int displacement = p.y - (SCREEN_HEIGHT-radius*2);
		p.y = (SCREEN_HEIGHT-radius*2) - displacement;
		yVel = -yVel * damping;
		xVel = xVel * damping;
	}
	if(p.x > SCREEN_WIDTH-radius*2)
	{
		int displacement = p.x - (SCREEN_WIDTH-radius*2);
		p.x = (SCREEN_WIDTH-radius*2) - displacement;
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
	if(lastMovement > 5)
		return true;
	else
		return false;
}

void Ball::bounce()
{
	//balls.push_back(Ball(rand()%20, rand()%-5, 0, 0.01, 0.7, DEFAULT_X_POSITION, DEFAULT_Y_POSITION));
	xVel = rand()%20;
	yVel = rand()%-5;
}

#endif