#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "Sound.h"

using namespace std;

/* This is a class that handles continuous explosions, it consists of
   of one sprite sheet that is created multiple times. The sprite will
   play a single explosion animation, and as that sprite enters a specific
   frame, it will start another explosion animation. This will happen 
   continuously until the explosion is turned off. The location of the
   sprites depend on a specific x1, x2, y1, and y2 locations that will
   select where the explosion will appear randomly within those coordinates.
   Each sprite is created as a struct and to communicate with each other, they
   will be put into a linked cycle list */
class Explosion
{
public:
	// Constructors and Destructors
	Explosion();
	~Explosion();
	
	// Turns on the explosion
	void turnOnExplosion();

	// Play the explosion within these coordinates
	void playExplosion(int X1, int X2, int Y1, int Y2);

	// Turn off the explosion
	void turnOffExplosion();

	// Reset the explosion and all of its variables
	void resetExplosion();

	// Fade the sound of the explosions
	void fadeSound();

private:
	// A structure that holds a single explosion sprite
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

	// The first sprite in the linked list
	sprite* startSprite;

	// The frame in which the next sprite in the list should begin playing
	int followFrame;

	// Flag to determine if the explosion is on
	bool on;

	// delay variables
	int delay;
	int maxDelay;
};

#endif // _EXPLOSION_H_