#include "Missile.h"
#include "idAssigner.h"
#include "Explosion.h"
#include "DarkGDK.h"
#include "RectangleObject.h"

void Missile::initialize()
{
	eState = eFlying;
	if(!facingRight)
		changeDirection();
	x = -200;
	speed = maxSpeed;
	if(dbRnd(1))
	{
		speed = maxSpeed * -1;
		x = 1100;
		changeDirection();
	}
	y = 163;

}

Missile::Missile()
{
	width = 106;
	height = 34;
	maxSpeed = 3;

	facingRight = false;


	// add all of the Missile's animations
												//x, y, flip, width, height, startFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Missile//Missile.bmp", 0, 0, 0, 1, 5, 0, 5, 8, 202, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Missile//Missile_Destroyed.bmp", -20, -12, 0, 2, 1, 0, 2, 16, 202, 200)); // delay is 8

	initialize();
}

Missile::~Missile()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}
void Missile::playAnimation()
{
	bool ended = false;
	int frame = -1;
	if(eState == eFlying)
		animations[0]->playAnimation(x, y, &frame, true, &ended);
	if(eState == eDestroyed)
		animations[1]->playAnimation(x, y, &frame, true, &ended);
	
}

void Missile::setAnimation(Missile::eAnimation animation)
{
	eState = animation;
	if(eState != eFlying)
		animations[0]->stopAnimation();
	if(eState != eDestroyed)
		animations[1]->stopAnimation();

}

// set which way he is facing (True -> Right, False -> Left)
void Missile::changeDirection()
{
	facingRight = !facingRight;
	for (int i = 0; i < animations.size(); i++)
		animations[i]->flipAnimation();
}

void Missile::checkTargetCollision(RectangleObject target, bool *hit)
{
	if(checkCollision(target))
	{
		initialize();
		*hit = true;
	}
}

void Missile::checkHitCollision(RectangleObject object, bool attacking)
{
	if(checkCollision(object) && attacking)
		initialize();
}

void Missile::firing()
{
	x += speed;
	playAnimation();
}