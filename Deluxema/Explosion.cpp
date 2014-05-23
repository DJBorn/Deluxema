#include "DarkGDK.h"
#include "Explosion.h"
#include "idAssigner.h"
#include "Sound.h"

using namespace std;

// Create a new animation
Explosion::Explosion()
{
	on = false;
	maxDelay = 2;
	delay = maxDelay - 1;
	followFrame = 5;

	startSprite = new sprite;
	startSprite->curFrame = 0;
	startSprite->id = generateid();
	startSprite->activated = false;
	startSprite->explosionSound = new Sound("includes//Sounds//Effects//Explosion.wav", 92);

	sprite* previousSprite = startSprite;

	dbCreateAnimatedSprite(startSprite->id,"includes//Sprites//Effects//Explosion.bmp", 4, 2, startSprite->id);
	dbScaleSprite(startSprite->id, 200);
	dbSetSpritePriority(startSprite->id, 201);
	//dbHideSprite(startSprite->id);

	// divide the number of frames in the explosion sprite (8) by the frequency and roof it
	// to get how many sprites are require to play the loop of explosions (iterate from 1 since we already created the first one)
	for(int i = 1; i < (8 + (followFrame - 1) - 1) / (followFrame - 1); i++)
	{
		sprite* newSprite;
		newSprite = new sprite;
		newSprite->curFrame = 0;
		newSprite->id = generateid();
		newSprite->activated = false;
		newSprite->explosionSound = new Sound("includes//Sounds//Effects//Explosion.wav", 92);

		previousSprite->child = newSprite;
		previousSprite = newSprite;

		if(i == (8 + (followFrame - 1) - 1) / (followFrame - 1) - 1)
			newSprite->child = startSprite;

		dbCreateAnimatedSprite(newSprite->id, "includes//Sprites//Effects//Explosion.bmp", 4, 2, newSprite->id);
		dbScaleSprite(newSprite->id, 200);
		dbSetSpritePriority(newSprite->id, 201);
		dbHideSprite(newSprite->id);
	}
}
Explosion::~Explosion()
{
	sprite* workingSprite;
	workingSprite = startSprite;
	for(int i = 0; i < (8 + (followFrame - 1) - 1) / (followFrame - 1); i++)
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
			sprite* workingSprite;
			workingSprite = startSprite;
			for(int i = 0; i < (8 + (followFrame - 1) - 1) / (followFrame - 1); i++)
			{
				if(workingSprite->activated)
				{
					workingSprite->curFrame++;
					if(workingSprite->curFrame == 1)
					{
						workingSprite->explosionSound->playSound();
						workingSprite->locationX = dbRnd(X2 - X1) + (X1 - 23);
						workingSprite->locationY = dbRnd(Y2 - Y1) + (Y1 - 22);
					}
					if(workingSprite->curFrame == followFrame)
						workingSprite->child->activated = true;
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
				workingSprite = workingSprite->child;
			}
		}
		else
		{
			sprite* workingSprite;
			workingSprite = startSprite;
			for(int i = 0; i < (8 + (followFrame - 1) - 1) / (followFrame - 1); i++)
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
				workingSprite = workingSprite->child;
			}
		}
	}
	sprite* workingSprite;
	workingSprite = startSprite;
	for(int i = 0; i < (8 + (followFrame - 1) - 1) / (followFrame - 1); i++)
	{
		// position the sprite and update it
		dbSprite(workingSprite->id, workingSprite->locationX, workingSprite->locationY, workingSprite->id);
		workingSprite = workingSprite->child;
	}
}