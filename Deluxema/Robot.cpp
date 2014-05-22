#include <vector>

// local functions
#include "RectangleObject.h"
#include "DarkGDK.h"
#include "Animation.h"
#include "Map.h"
#include "Robot.h"
#include "Map.h"
#include "Ace.h"
#include "Sound.h"
#include <vld.h>
using namespace std;

void Robot::initialize()
{
	speed = 0;
	maxSpeed = 20;
	maxSpeedTimer = 0;
	maxSpeedDuration = 20;
	dashDelay = 0;
	maxDashDelay = dbRnd(100) + 40;
	speedingUp = false;
	setAnimation(eStand);

	x = dbRnd(100) - 300;
	if(dbRnd(1))
		x = dbRnd(100) + 1200;
	y = 291;
}

// Position and create his attacks when Robot is created
Robot::Robot() : Character(48, 32),
dashSound("includes//Sounds//Effects//Robot//Robot_Dash.wav", 100),
deathSound("includes//Sounds//Effects//Robot//Robot_Death.wav", 100)
{
	respawnTimer = 0;
	respawnDuration = 500;

	width = 34;
	height = 94;

	// add all of Robot's animations
								//x, y, flip, width, height, startFrame, curFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Stand.bmp", -8, -14, -2, 4, 1, 0, 4, 12, 200, 200)); // delay is 12
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Dash.bmp", -28, -14, 10, 3, 1, 0, 3, 3, 200, 200)); // delay is 3
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Run.bmp", -32, -14, 18, 1, 1, 0, 1, 1, 200, 200));// delay is 1
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Punch.bmp", -32, -10, -12, 4, 3, 0, 9, 4, 200, 200)); // delay is 4
	animations.push_back(new Animation("includes//Sprites//Robot//Robot_Death.bmp", -12, -6, -4, 2, 1, 0, 2, 5, 200, 200)); // delay is 5
	animations.push_back(new Animation("includes//Sprites//Robot//robothitbox.bmp", 0, 0, 0, 1, 1, 1, 0, 1, 199, 200)); //TEMPORARY GET RID
	animations.push_back(new Animation("includes//Sprites//Robot//punchhitbox.bmp", 0, 0, 0, 1, 1, 1, 0, 1, 199, 200)); //TEMPORARY GET RID

	initialize();
}

Robot::~Robot()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}

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
	}
	if(eStance == ePunch)
	{
		animations[3]->playAnimation(x, y, &frame, false, &ended);

		// If this reaches the attacking frames, activate the robots punch
		if(3 <= frame && frame <= 8)
		{
			attacking = true;
			int addFlip = 0;

			// reposition the robot's punch hit box
			if(!facingRight)
				addFlip = -62;
			attack.x = x + 24 + addFlip;
			attack.y = y + 12;

			//animations[6]->playAnimation(attack.x, attack.y, &frame, true, &ended); // TEMPORARY GET RID	
		}
		else
			attacking = false;
		if(ended)
		{
			setAnimation(eRun);
			animations[2]->playAnimation(x, y, &frame, false, &ended);
		}
	}
	if(eStance == eDie)
	{
		animations[4]->playAnimation(x, y, &frame, true, &ended);
	}
	//animations[5]->playAnimation(x, y, &frame, true, &ended); // TEMPORARY
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

void Robot::respawn()
{
	initialize();
}

void Robot::AI(Ace *ace, Map *map)
{
	int robotHorizontalMove = 0;

	// if the robot is not dying, increment the dashDelay
	if(eStance != eDie)
		dashDelay++;

	if(eStance == eDie)
	{
		if(!flying)
			respawn();
		else
			robotHorizontalMove = speed;
	}

	// constantly reposition the robot's punch hit box to check if it can land a hit on Ace
	int addFlip;
	if(!facingRight)
		addFlip = -62;
	attack.x = x + 24 + addFlip;
	attack.y = y + 12;


	if(ace->Attacking() && ace->getAttack().checkCollision(RectangleObject(*this)) && eStance != eDie)
	{
		deathSound.playSound();
		if(ace->getFacingRight())
			speed = 3;
		else
			speed = -3;
		fall = -4;
		setAnimation(eDie);
	}


	// the robot can only change directions when it is standing
	if(eStance == eStand)
	{
		if((ace->x + ace->width/2) < (x + width/2) && facingRight)
			changeDirection();
		else if((ace->x + ace->width/2) >= (x + width/2) && !facingRight)
			changeDirection();

		// set the robot's max speed
		maxSpeed = 6;

		// set the robot's max speed duration
		maxSpeedDuration = dbRnd(5) + 50;

		punched = false;
	}

	// once the robot is able to dash set the initial values its dashing variables
	if(dashDelay == maxDashDelay)
	{
		dashSound.playSound();
		// It will be speeding up initially
		speedingUp = true;
		// set the animation to dashing
		setAnimation(eDash);
		// set the maxSpeedTimer to 0
		maxSpeedTimer = 0;
	}

	// if statement for the robots horizontal movements and animations
	if(eStance == eDash || eStance == eRun || eStance == ePunch)
	{
		// reset the dash delay
		dashDelay = 0;

		// if the robot is facing left, make it move left
		if(!facingRight)
		{
			// if the robot is speeding up, keep increasing its speed
			if(speedingUp)
				speed--;
			// if the robot has reached its max speed duration, start slowing down
			else if(maxSpeedTimer == maxSpeedDuration)
				speed++;
			// if the robot has reached its max speed, start the max speed timer for the duration
			if(speed * -1 == maxSpeed)
			{
				// the robot is no longer speeding up
				speedingUp = false;
				maxSpeedTimer++;
			}
		}
		// reversed for facing right
		else if(facingRight)
		{
			if(speedingUp)
				speed++;
			else if(maxSpeedTimer == maxSpeedDuration)
				speed--;
			if(speed == maxSpeed)
			{
				speedingUp = false;
				maxSpeedTimer++;
			}
		}

		// if the robots speed is 0, he has finished his dash and is not standing
		if(speed == 0)
		{
			// make sure he is not attacking
			attacking = false;
			setAnimation(eStand);
		}
		// otherwise, check if Ace is in range for a punch, then activate it
		else if(abs((ace->x + ace->width/2) - (x + width/2)) < 200 && !punched || eStance == ePunch)
		{
			setAnimation(ePunch);
			punched = true;
		}

		// set the movement for this frame
		robotHorizontalMove = speed;
	}

	// play the robot's animation
	playAnimation();

	// move the robot on the map
	move(robotHorizontalMove, fall, map);
}