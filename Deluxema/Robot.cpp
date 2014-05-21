#include <vector>

// local functions
#include "RectangleObject.h"
#include "Animation.h"
#include "Map.h"
#include "Robot.h"
#include "Sound.h"
#include <vld.h>
using namespace std;

// Position and create his attacks when Robot is created
Robot::Robot(int x, int y) : Character(44, 38)
{
	speed = 5;

	Robot::x = x;
	Robot::y = y;
	eStance = eStand;

	width = 28;
	height = 74;
/*
	// add all of Robot's animations
								//x, y, flip, width, height, startFrame, curFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Stand.bmp", -20, -12, -34, 4, 2, 0, 8, 8, 200, 200)); // delay is 6
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Run.bmp", -62, -14, 50, 5, 2, 0, 10, 3, 200, 200)); // delay is 3
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Slice.bmp", -86, -30, -26, 5, 2, 0, 10, 2, 200, 200));// delay is 2
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Jump_Slash.bmp", -108, -30, 18, 3, 3, 0, 9, 2, 200, 200)); // delay is 2
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Jump.bmp", -58, 0, 50, 1, 1, 1, 0, 1, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Hurt.bmp", -34, -24, -2, 1, 1, 1, 0, 1, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Robothitboxh.bmp", 0, 0, 0, 1, 1, 1, 0, 1, 200, 200)); //TEMPORARY GET RID
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Ground_Slash.bmp", 0, 0, 0, 1, 1, 1, 0, 1, 199, 200)); //TEMPORARY GET RID
	*/
}

Robot::~Robot()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}


void Robot::playAnimation()
{
}

void Robot::setAnimation(Robot::eAnimation animation)
{
}


void Robot::move(int x, int y, Map *map)
{
}

bool Robot::checkStance(Robot::eAnimation stance)
{
	if(stance == eStance)
		return true;
	return false;
}

