#include "Sparkle.h"
#include "DarkGDK.h"
#include "idAssigner.h"

Sparkle::Sparkle(int x, int y, int frequency)
{
	id = generateid();
	Sparkle::x = x;
	Sparkle::y = y;
	maxFrequency = frequency;
	Sparkle::frequency = 0;
	delay = 0;
	maxDelay = 1;
	frame = -1;
	maxFrame = 17;
	glow = true;

	dbCreateAnimatedSprite(id, "includes//Sprites//Effects//Sparkle.bmp", 4, 5, id);
	
	// scale the sprite
	dbScaleSprite(id, 200);
	// set the sprite priority
	dbSetSpritePriority(id, 203);
	// initially hide the sprite till called to play
	dbHideSprite(id);
}

Sparkle::~Sparkle()
{
	dbDeleteSprite(id);
	deleteid(id);
}

void Sparkle::playSparkle()
{
	// increment frequency until the sparkle is ready to shine again
	frequency++;
	if(frequency > maxFrequency)
	{
		// play the animation by glowing bright then dimming back down
		delay++;
		if(delay == maxDelay)
		{
			delay = 0;
			if(glow)
				frame++;
			else
				frame--;
			dbSetSpriteFrame(id, frame);
			dbShowSprite(id);
			dbSprite(id, x, y, id);
			
			if(frame == maxFrame)
				glow = false;
			else if(frame == 0 && !glow)
			{
				glow = true;
				frequency = 0;
				dbHideSprite(id);
			}
		}
	}
}

void Sparkle::resetSparkle()
{
	frequency = 0;
	delay = 0;
	frame = -1;
	glow = true;
	dbHideSprite(id);
}