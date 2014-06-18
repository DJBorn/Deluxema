#include "Mirror.h"
#include "idAssigner.h"
#include "DarkGDK.h"
#include <vector>

void Mirror::initialize(int x, int y)
{
	Mirror::x = x;
	Mirror::y = y;
	setAnimation(eMirror1);

	// vertical movement initializations
	verticalDelay = 0;
	maxVerticalDelay = 10;
	vUnitsShifted = 0;
	shiftingUp = true;

	// horizontal movement initializations
	horizontalMoveDelay = 0;
	maxHorizontalMoveDelay = 300;
	curSpeed = 0;
	maxSpeed = 3;
	maxSpeedTimer = 0;
	maxSpeedDuration = 50;
	horizontalDelay = 0;
	maxHorizontalDelay = 1;
	hDashes = 0;
	dashingRight = true;

	destroyed = false;
}

Mirror::Mirror(int x, int y)
{

	width = 68;
	height = 88;

	// add all of the Mirror's animations
								//x, y, flip, width, height, startFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror1.bmp", -36, -36, 0, 4, 2, 0, 8, 16, 199, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror2.bmp", -36, -36, 0, 4, 2, 0, 8, 16, 199, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror3.bmp", -36, -36, 0, 4, 2, 0, 8, 16, 199, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror4.bmp", -36, -36, 0, 4, 2, 0, 8, 16, 199, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror5.bmp", -36, -36, 0, 4, 2, 0, 8, 16, 199, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror_Break.bmp", -36, -36, 0, 4, 3, 0, 12, 2, 199, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Mirror//Mirror_Hitbox.bmp", 0, 0, 0, 1, 1, 0, 1, 1, 200, 200)); //TEMPORARY GET RID

	initialize(x, y);
}

Mirror::~Mirror()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}
void Mirror::playAnimation()
{
	bool ended = false;
	int frame = -1;
	if(eState == eMirror1)
		animations[0]->playAnimation(x, y, &frame, true, &ended);
	if(eState == eMirror2)
		animations[1]->playAnimation(x, y, &frame, true, &ended);
	if(eState == eMirror3)
		animations[2]->playAnimation(x, y, &frame, true, &ended);
	if(eState == eMirror4)
		animations[3]->playAnimation(x, y, &frame, true, &ended);
	if(eState == eMirror5)
		animations[4]->playAnimation(x, y, &frame, true, &ended);
	if(eState == eMirrorBreak)
		animations[5]->playAnimation(x, y, &frame, true, &ended);
	
	//animations[6]->playAnimation(x, y, &frame, true, &ended); // TEMPORARY GET RID
}

void Mirror::setAnimation(Mirror::eAnimation animation)
{
	eState = animation;
	if(eState != eMirror1)
		animations[0]->stopAnimation();
	if(eState != eMirror2)
		animations[1]->stopAnimation();
	if(eState != eMirror3)
		animations[2]->stopAnimation();
	if(eState != eMirror4)
		animations[3]->stopAnimation();
	if(eState != eMirror5)
		animations[4]->stopAnimation();
	if(eState != eMirrorBreak)
		animations[5]->stopAnimation();

}

void Mirror::hit()
{
	if(eState == eMirror1)
		setAnimation(eMirror2);
	else if(eState == eMirror2)
		setAnimation(eMirror3);
	else if(eState == eMirror3)
		setAnimation(eMirror4);
	else if(eState == eMirror4)
		setAnimation(eMirror5);
	else
	{
		destroyed = true;
		setAnimation(eMirrorBreak);
	}
}

void Mirror::moveVertical()
{
	// how much to move the mirror by vertically
	int verticalMove = 0;

	// the delay to determine how often to move it
	verticalDelay++;
	if(verticalDelay > maxVerticalDelay)
	{
		verticalDelay = 0;
		if(shiftingUp)
		{
			// if the mirror is moving up, set the vertical move to go up
			verticalMove = -1;

			// increment the Units shifted up
			vUnitsShifted += 1;

			// if the mirror has moved 2 units up, start moving it down
			if(vUnitsShifted == 2)
				shiftingUp = false;
		}
		else
		{
			verticalMove = 1;
			vUnitsShifted -= 1;
			if(vUnitsShifted == -2)
				shiftingUp = true;
		}

	}
	y += verticalMove;
}
void Mirror::moveHorizontal()
{
	int horizontalMove = 0;
	horizontalMoveDelay++;

	// the delay to determine how often to dash it
	if(horizontalMoveDelay > maxHorizontalMoveDelay)
	{
		horizontalDelay++;
		// the delay to determine how often to move it
		if(horizontalDelay > maxHorizontalDelay)
		{
			horizontalDelay = 0;
			if(dashingRight)
			{
				// if the mirror is accelerating, increase its speed
				if(speedingUp)
					curSpeed++;

				// if the mirror has reached its max speed duration, decrease its speed
				else if(maxSpeedTimer == maxSpeedDuration)
					curSpeed--;

				// if the mirror reached its max speed, stop it from speeding up and start the max speed timer
				if(abs(curSpeed) == maxSpeed)
				{
					speedingUp = false;
					maxSpeedTimer++;
				}

				// if the mirrors speed is 0, then the dash has completed, reset all variables
				if(curSpeed == 0)
				{
					maxSpeedTimer = 0;
					speedingUp = true;
					horizontalMoveDelay = 0;

					// update the mirrors location
					hDashes++;
					if(hDashes == 1)
						dashingRight = false;
				}
			}
			// reversed for moving left
			else
			{
				if(speedingUp)
					curSpeed--;
				else if(maxSpeedTimer == maxSpeedDuration)
					curSpeed++;

				if(abs(curSpeed) == maxSpeed)
				{
					speedingUp = false;
					maxSpeedTimer++;
				}
				if(curSpeed == 0)
				{
					maxSpeedTimer = 0;
					speedingUp = true;
					horizontalMoveDelay = 0;
					hDashes--;
					if(hDashes == -1)
						dashingRight = true;
				}
			}
			horizontalMove = curSpeed;
		}

	}
	x += horizontalMove;
}


bool Mirror::Destroyed()
{
	return destroyed;
}