#include "DarkGDK.h"
#include "Explosion.h"
#include "idAssigner.h"
#include "Sound.h"

using namespace std;

void Explosion::resetExplosion()
{
	sprite* workingSprite;
	workingSprite = startSprite;
	for(int i = 0; i < 10; i++)
	{
		sprite* nextSprite = workingSprite->child;
		workingSprite->activated = false;
		workingSprite->curFrame = 0;
		dbHideSprite(workingSprite->id);
		workingSprite = nextSprite;
	}
}
// Create a new animation
Explosion::Explosion()
{
	on = false;
	maxDelay = 4;
	delay = maxDelay - 1;

	// Set the frame in which the next explosion will begin to play
	followFrame = 3;
	int volume = 87;

	// Create the first sprite
	startSprite = new sprite;
	startSprite->curFrame = 0;
	startSprite->id = generateid();
	startSprite->activated = false;
	startSprite->explosionSound = new Sound("includes//Sounds//Effects//Explosion.wav", volume);

	// Remember the previous sprite to link it to its child
	sprite* previousSprite = startSprite;

	// Load the sprite with the struct data
	dbCreateAnimatedSprite(startSprite->id,"includes//Sprites//Effects//Explosion.bmp", 4, 2, startSprite->id);
	dbScaleSprite(startSprite->id, 200);
	dbSetSpritePriority(startSprite->id, 205);
	dbHideSprite(startSprite->id);

	// Create 9 more sprites. (The explosion animation has 8 frames, so 10 sprites should be plenty)
	for(int i = 1; i < 10 ; i++)
	{
		sprite* newSprite;
		newSprite = new sprite;
		newSprite->curFrame = 0;
		newSprite->id = generateid();
		newSprite->activated = false;
		newSprite->explosionSound = new Sound("includes//Sounds//Effects//Explosion.wav", volume);

		previousSprite->child = newSprite;
		previousSprite = newSprite;

		if(i == 9)
			newSprite->child = startSprite;

		dbCreateAnimatedSprite(newSprite->id, "includes//Sprites//Effects//Explosion.bmp", 4, 2, newSprite->id);
		dbScaleSprite(newSprite->id, 200);
		dbSetSpritePriority(newSprite->id, 205);
		dbHideSprite(newSprite->id);
	}
}
Explosion::~Explosion()
{
	// Delete all sprites
	sprite* workingSprite;
	workingSprite = startSprite;
	for(int i = 0; i < 10; i++)
	{
		sprite* nextSprite = workingSprite->child;
		deleteid(workingSprite->id);
		delete workingSprite->explosionSound;
		delete workingSprite;
		workingSprite = nextSprite;
	}
}

void Explosion::turnOnExplosion()
{
	on = true;
	startSprite->activated = true;
}
void Explosion::turnOffExplosion()
{
	on = false;
}

void Explosion::playExplosion(int X1, int X2, int Y1, int Y2)
{
	delay++;
	if(delay == maxDelay)
	{
		delay = 0;
		if(on)
		{
			// Create a pointer to the currently working sprite
			sprite* workingSprite;

			// Set the working sprite as the first sprite in the explosion
			workingSprite = startSprite;
			for(int i = 0; i < 10; i++)
			{
				// The current sprite must be active
				if(workingSprite->activated)
				{
					// Increment the frame
					workingSprite->curFrame++;

					// If it has just begun, play the explosion sound and randomize its location
					if(workingSprite->curFrame == 1)
					{
						workingSprite->explosionSound->playSound();
						workingSprite->locationX = dbRnd(X2 - X1) + (X1 - 23);
						workingSprite->locationY = dbRnd(Y2 - Y1) + (Y1 - 22);
					}
					// If the current frame is the followFrame, then activate its child to play
					if(workingSprite->curFrame == followFrame)
					{
						workingSprite->child->activated = true;
						// If this is the last sprite in the list, then play the first sprite again on this iteration
						// (This is because all the other sprites would've been able to play atleast once
						//  on the iteration they were activated in EXCEPT the first one)
						if(i == 9)
							i--;
					}
					// If it has reached its final frame, deactivate the sprite, reset its frame, and hide the sprite
					if(workingSprite->curFrame > 8)
					{
						workingSprite->curFrame = 0;
						workingSprite->activated = false;
						dbHideSprite(workingSprite->id);
					}
					else
					{
						dbSetSpriteFrame(workingSprite->id, workingSprite->curFrame);
						dbShowSprite(workingSprite->id);
					}
				}
				// update the sprite on the screen
				dbSprite(workingSprite->id, workingSprite->locationX, workingSprite->locationY, workingSprite->id);
				// set the next working sprite as the child
				workingSprite = workingSprite->child;
			}
		}
		else
		{
			// If the explosion has turned off, then repeat steps above except do not activate on the follow frame
			sprite* workingSprite;
			workingSprite = startSprite;
			for(int i = 0; i < 10; i++)
			{
				if(workingSprite->activated)
				{
					workingSprite->curFrame++;
					if(workingSprite->curFrame == 1)
					{
						workingSprite->locationX = dbRnd(X2 - X1) + (X1 - 23);
						workingSprite->locationY = dbRnd(Y2 - Y1) + (Y1 - 22);
					}
					if(workingSprite->curFrame > 8)
					{
						workingSprite->curFrame = 0;
						workingSprite->activated = false;
						dbHideSprite(workingSprite->id);
					}
					else
					{
						dbSetSpriteFrame(workingSprite->id, workingSprite->curFrame);
						dbShowSprite(workingSprite->id);
					}
				}
				dbSprite(workingSprite->id, workingSprite->locationX, workingSprite->locationY, workingSprite->id);
				workingSprite = workingSprite->child;
			}
		}
	}
}

void Explosion::fadeSound()
{
	sprite* workingSprite;
	workingSprite = startSprite;
	for(int i = 0; i < 10; i++)
	{
		sprite* nextSprite = workingSprite->child;
		workingSprite->explosionSound->stopSound();
		workingSprite = nextSprite;
	}
}