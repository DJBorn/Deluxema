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

void Animation::playAnimation(int x, int y)
{
	// increase the delay counter
	delay++;

	// set the next frame with the delay has finished
	if(delay == maxDelay)
	{
		delay = 0;

		// set the frame
		dbSetSpriteFrame(id, curFrame);

		// set the next frame
		curFrame++;

		// if it went over its max frame, reset the frame to the start frame
		if(curFrame > maxFrame)
			curFrame = startFrame;
	}
	// refresh the sprite
	int addFlip = 0;
	if(flipped)
		addFlip = flip;

	// position the sprite and display it
	dbSprite(id, x + Animation::x + addFlip, y + Animation::y, id);
	dbShowSprite(id);
}

void Animation::stopAnimation(){ dbHideSprite(id);}

void Animation::flipAnimation() 
{ 
	dbMirrorSprite(id);
	flipped = !flipped;
}