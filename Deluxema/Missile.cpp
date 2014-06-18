#include "Missile.h"
#include "idAssigner.h"
#include "Explosion.h"
#include "DarkGDK.h"
#include "RectangleObject.h"
#include "Map.h"

void Missile::initialize()
{
	explosion.turnOffExplosion();
	resetSounds();
	setAnimation(eFlying);
	if(!facingRight)
		changeDirection();
	x = dbRnd(100) - 300;
	speed = maxSpeed;
	if(dbRnd(1))
	{
		speed = maxSpeed * -1;
		x = dbRnd(100) + 1100;
		changeDirection();
	}
	y = 163;

}

Missile::Missile() : Explode("includes//Sounds//Effects//Missile_Explosion.wav", 90)
{
	width = 106;
	height = 34;
	maxSpeed = 2;

	facingRight = false;


	// add all of the Missile's animations
												//x, y, flip, width, height, startFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Missile//Missile.bmp", 0, 0, 0, 1, 5, 0, 5, 8, 202, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Missile//Missile_Destroyed.bmp", -20, -12, 0, 2, 1, 0, 2, 5, 202, 200)); // delay is 8

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
	if(checkCollision(target) && eState != eDestroyed)
	{
		initialize();
		*hit = true;
		Explode.playSound();
	}
}

void Missile::respawn()
{
	initialize();
}

void Missile::checkHitCollision(RectangleObject object, bool attackerFacingRight, bool attacking, int &score)
{
	if(checkCollision(object) && attacking && eState != eDestroyed)
	{
		score++;
		explosion.turnOnExplosion();
		if(attackerFacingRight)
			speed = 3;
		else
			speed = -3;
		fall = -4;
		setAnimation(eDestroyed);
	}
}

void Missile::AI(Map *map)
{
	x += speed;
	if(eState == eDestroyed)
	{
		y += fall;
		if(map->checkGlobalHitBox((RectangleObject)*this))
		{
			initialize();
		}
	}
	playAnimation();
}

void Missile::Gravity(double gravity)
{
	if(eState == eDestroyed)
		fall += gravity;
}

void Missile::playExplosion()
{
	explosion.playExplosion(x, x + width, y, y + height);
}


void Missile::fadeSounds()
{
	Explode.fade();
	explosion.fadeSound();
}

void Missile::resetSounds()
{
	Explode.resetVolume();
}

void Missile::resetExplosion()
{
	explosion.resetExplosion();
}