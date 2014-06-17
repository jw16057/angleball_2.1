#ifndef __ball_h
#define __ball_h

#include <deque>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int SCREEN_BPP = 32;
const int DEFAULT_BALL_RADIUS = 16;
const int DEFAULT_Y_POSITION = SCREEN_HEIGHT - (DEFAULT_BALL_RADIUS * 2);
const int DEFAULT_X_POSITION = 0;
const double DEFAULT_DAMPING = 0.4;

struct Pos{
	Pos(){x = 0; y = 0;}
	Pos(double x_, double y_): x(x_), y(y_) {}
	double x;
	double y;
	bool operator == (Pos r)
	{
		if(floor(x) == floor(r.x) && floor(y) == floor(r.y))
			return true;
		else
			return false;
	}
};
class Ball{
public:
	Ball();
	Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping, double x_, double y_);
	void tick();
	bool isStill();
	void bounce();

	double getX() {return p.x;}
	double getY() {return p.y;}
private:
	Pos p;
	int lastMovement;
	int radius;
	double xVel;
	double yVel;
	double xAccel;
	double yAccel;
	double damping;
	std::deque<Pos> historyPos;
};

#endif