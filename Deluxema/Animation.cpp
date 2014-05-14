#include "DarkGDK.h"
#include "Animation.h"
#include "idAssigner.h"

using namespace std;

// Create a new animation
Animation::Animation(char* path, int x, int y, int flip, int width, int height, int startFrame,
					 int curFrame, int maxFrame, int maxDelay, int priority, int scale)
{
	Animation::x = x;
	Animation::y = y;
	Animation::flip = flip;
	Animation::path = path;
	Animation::startFrame = startFrame;
	Animation::curFrame = curFrame;
	Animation::maxFrame = maxFrame;
	Animation::delay = 0;
	Animation::maxDelay = maxDelay;
	Animation::id = generateid();
	flipped = false;

	// load the sprite
	dbCreateAnimatedSprite(id, path, width, height, id);
	// scale the sprite
	dbScaleSprite(id, scale);
	// set the sprite priority
	dbSetSpritePriority(id, priority);
	// initially hide the sprite till called to play
	dbHideSprite(id);
}

Animation::~Animation()
{
	// delete the sprite and give back the id
	dbDeleteSprite(id);
	deleteid(id);
}


void Animation::playAnimation(int x, int y, int *frame, bool repeat, bool *ended)
{
	// increase the delay counter
	delay++;

	// set the next frame when the delay has finished
	if(delay == maxDelay)
	{
		delay = 0;


		// set the next frame
		curFrame++;

		// set the frame
		dbSetSpriteFrame(id, curFrame);
		*frame = curFrame;

	
		// if the animation is on loop and it has reached its max frame, then reset the animation
		if(curFrame == maxFrame && repeat)
			curFrame = startFrame;

		// if it went over its max frame, reset the frame to the start frame ( the reason is because it should run the last frame
		// atleast once before exiting this animation, which it will after this if statement since we declared *ended as true)
		if(curFrame > maxFrame)
		{
			curFrame = startFrame;
			if(!repeat)
				*ended = true;
		}
	}
	// refresh the sprite
	int addFlip = 0;
	if(flipped)
		addFlip = flip;

	// position the sprite and display it
	dbShowSprite(id);
	dbSprite(id, x + Animation::x + addFlip, y + Animation::y, id);
}

void Animation::stopAnimation()
{ 
	// reset the animation
	curFrame = startFrame;
	// hide the sprite
	dbHideSprite(id);
	delay = maxDelay - 1;
}

void Animation::flipAnimation() 
{ 
	dbMirrorSprite(id);
	flipped = !flipped;
}