#include <vector>

// local functions
#include "RectangleObject.h"
#include "Animation.h"
#include "Map.h"
#include "Robot.h"
#include "Map.h"
#include "Ace.h"
#include "Sound.h"
#include <vld.h>
using namespace std;

// Position and create his attacks when Robot is created
Robot::Robot(int x, int y) : Character(48, 32)
{
	speed = 3;

	Robot::x = x;
	Robot::y = y;
	eStance = eStand;

	width = 34;
	height = 94;

	// add all of Robot's animations
								//x, y, flip, width, height, startFrame, curFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Stand.bmp", -8, -14, -2, 4, 1, 0, 4, 12, 200, 200)); // delay is 12
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Dash.bmp", -28, -14, 10, 3, 1, 0, 3, 3, 200, 200)); // delay is 3
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Run.bmp", -32, -14, 18, 1, 1, 0, 1, 1, 200, 200));// delay is 1
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Punch.bmp", -32, -10, -12, 4, 3, 0, 9, 4, 200, 200)); // delay is 4
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Death.bmp", -12, -6, -4, 2, 1, 0, 2, 5, 200, 200)); // delay is 5
	animations.push_back(new Animation("includes//Sprites//Robot//robothitbox.bmp", 0, 0, 0, 1, 1, 1, 0, 1, 200, 200)); //TEMPORARY GET RID
	animations.push_back(new Animation("includes//Sprites//Robot//punchhitbox.bmp", 0, 0, 0, 1, 1, 1, 0, 1, 199, 200)); //TEMPORARY GET RID
	
	eStance = ePunch;
}

Robot::~Robot()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}

int counter = 0; //temp
void Robot::playAnimation()
{
	bool ended = false;
	int frame = -1;
	if(eStance == eStand)
		animations[0]->playAnimation(x, y, &frame, true, &ended);
	if(eStance == eDash)
	{
		animations[1]->playAnimation(x, y, &frame, false, &ended);
		if(ended)
			setAnimation(eRun);
	}
	if(eStance == eRun)
	{
		animations[2]->playAnimation(x, y, &frame, true, &ended);
		counter++;
		if(counter == 50)
		{
			counter = 0;
			setAnimation(eDash);
		}
	}
	if(eStance == ePunch)
	{
		animations[3]->playAnimation(x, y, &frame, true, &ended);

		// If this reaches the attacking frames, activate the robots punch
		if(3 <= frame && frame <= 8)
		{
			attacking = true;
			int addFlip = 0;

			// reposition the robot's slice hit box
			if(!facingRight)
				addFlip = -62;
			attack.x = x + 24 + addFlip;
			attack.y = y + 12;

			animations[6]->playAnimation(attack.x, attack.y, &frame, true, &ended); // TEMPORARY GET RID	
		}
		else
			attacking = false;
	}
	if(eStance == eDie)
	{
		animations[4]->playAnimation(x, y, &frame, true, &ended);
	}
	animations[5]->playAnimation(x, y, &frame, true, &ended); // TEMPORARY
}

void Robot::setAnimation(Robot::eAnimation animation)
{
	eStance = animation;
	if(eStance != eStand)
		animations[0]->stopAnimation();
	if(eStance != eDash)
		animations[1]->stopAnimation();
	if(eStance != eRun)
		animations[2]->stopAnimation();
	if(eStance != ePunch)
		animations[3]->stopAnimation();
	if(eStance != eDie)
		animations[4]->stopAnimation();
}


void Robot::move(int x, int y, Map *map)
{
	Robot::x += x;
	while(map->checkGlobalHitBox((RectangleObject)*this))
	{
		if(x > 0)
			Robot::x -= 1;
		else
			Robot::x += 1;
	}

	if(y < 0)
	{
		flying = true;
	}
	Robot::y += y;

	while(map->checkGlobalHitBox((RectangleObject)*this))
	{
		if(flying)
			stopAceSlice();
		if(y > 0)
			Robot::y -= 1;
		else
			Robot::y += 1;
		fall = 0;
		flying = false;
	}
}

bool Robot::checkStance(Robot::eAnimation stance)
{
	if(stance == eStance)
		return true;
	return false;
}

void Robot::AI(Ace *ace, Map *map)
{
	int robotHorizontalMove = 0;

	if(ace->x + ace->width < x && facingRight)
		changeDirection();
	else if(x + width < ace->x && !facingRight)
		changeDirection();

	// play the robot's animation
	playAnimation();

	// move the robot on the map
	move(robotHorizontalMove, fall, map);
}