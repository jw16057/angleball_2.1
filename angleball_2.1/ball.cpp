#ifndef __ball_cpp
#define __ball_cpp
#include "ball.h"

double symmetric_round(double);

Ball::Ball()
{
	radius = DEFAULT_BALL_RADIUS;
	damping = DEFAULT_DAMPING;

	x = 0;
	y = SCREEN_HEIGHT - (radius * 2);

	xVel = 0;
	yVel = 0;

	xAccel = 0;
	yAccel = gravity;
}

Ball::Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping_, double x_, double y_)
{
	radius = DEFAULT_BALL_RADIUS;
	x = x_;
	y = y_;
	
	xVel = xVel_;
	yVel = yVel_;
	xAccel = xAccel_;
	yAccel = yAccel_;
	damping = damping_;
}

void Ball::tick()
{
	x += xVel;
	y += yVel;

	xVel += xAccel;
	yVel += yAccel;
	

	if(y > SCREEN_HEIGHT-radius*2)
	{
		int displacement = y - (SCREEN_HEIGHT-radius*2);
		y = (SCREEN_HEIGHT-radius*2) - displacement;
		yVel = -yVel * damping;
		xVel = xVel * damping;
	}
	if(x > SCREEN_WIDTH-radius*2)
	{
		int displacement = x - (SCREEN_WIDTH-radius*2);
		x = (SCREEN_WIDTH-radius*2) - displacement;
		yVel = yVel * damping;
		xVel = -xVel * damping;
		
	}
	if(x < 0)
	{
		x = -x;
		yVel = yVel * damping;
		xVel = -xVel * damping;
	}
}


#endif