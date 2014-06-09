#ifndef __ball_h
#define __ball_h

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int SCREEN_BPP = 32;
const int DEFAULT_BALL_RADIUS = 16;
const int DEFAULT_Y_POSITION = SCREEN_HEIGHT - (DEFAULT_BALL_RADIUS * 2);
const int DEFAULT_X_POSITION = 0;
const double DEFAULT_DAMPING = 0.4;
const double gravity = 9.8;

class Ball{
public:
	Ball();
	Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping, double x_, double y_);
	void tick();
	double x;
	double y;
	int radius;
	double xVel;
	double yVel;
	double xAccel;
	double yAccel;
	double damping;
};

#endif