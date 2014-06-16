#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "Sound.h"

using namespace std;

class Explosion
{
public:
	Explosion();
	~Explosion();
	
	void turnOnExplosion();
	void playExplosion(int X1, int X2, int Y1, int Y2);
	void turnOffExplosion();
	void fadeSound();

private:
	struct sprite
	{
		bool activated;
		int id;
		int curFrame;
		int locationX;
		int locationY;
		sprite* child;
		Sound* explosionSound;
	};
	sprite* startSprite;
	int followFrame;
	bool on;
	int x1, x2, y1, y2;
	int delay;
	int maxDelay;
};

#endif // _EXPLOSION_H_