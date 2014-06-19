#ifndef __ball_h
#define __ball_h

#include "SDL.h"
#include "SDL_image.h"

#include <deque>

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
	Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping, double x_, double y_);
	void tick(int screenWidth, int screenHeight);
	bool isStill();
	void bounce();
	void changePos(Pos xy);
	void changeVel(double x, double y);

	double getX() {return p.x;}
	double getY() {return p.y;}
	SDL_Surface * getFace() {return face;};
private:
	Pos p;
	int lastMovement;
	int radius;
	double xVel;
	double yVel;
	double xAccel;
	double yAccel;
	double damping;
	SDL_Surface *face;
	std::deque<Pos> historyPos;
};

#endif