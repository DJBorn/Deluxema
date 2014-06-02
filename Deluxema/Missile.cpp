#include "Missile.h"
#include "idAssigner.h"
#include "DarkGDK.h"

void Missile::initialize()
{
	x = -200;
	if(dbRnd(1))
		x = 1100;
	y = 300;

}

Missile::Missile()
{
	width = 106;
	height = 34;

	// add all of the Missile's animations
												//x, y, flip, width, height, startFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Missile//Missile.bmp", -36, -36, 0, 1, 5, 0, 5, 16, 202, 200)); // delay is 8
	animations.push_back(new Animation("includes//Sprites//Missile//Missile_Destroyed.bmp", -20, -12, 0, 2, 1, 0, 2, 16, 202, 200)); // delay is 8
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