#include <vector>

// local functions
#include "RectangleObject.h"
#include "Animation.h"
#include "Map.h"
#include "Ace.h"

using namespace std;

Ace::Ace(int x, int y)
{
	aceSpeed = 5;
	aceFall = 0;

	leftConstant = 0;

	Ace::x = x;
	Ace::y = y;
	eStance = eStand;

	facingRight = true;
	flying = false;

	width = 28;
	height = 74;

	// add all of Ace's animations
								//x, y, flip, width, height, startFrame, curFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Stand.bmp", -20, -12, -34, 4, 2, 1, 1, 8, 6, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Run.bmp", -62, -14, 50, 5, 2, 1, 1, 10, 3, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Slice.bmp", -86, -30, -26, 5, 2, 1, 1, 10, 2, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Jump_Slash.bmp", -108, -30, 18, 3, 3, 1, 1, 9, 2, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Jump.bmp", -58, 0, 50, 1, 1, 1, 1, 1, 1, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Hurt.bmp", -34, -24, -2, 1, 1, 1, 1, 1, 1, 200, 200));
	//animations.push_back(new Animation("includes//Sprites//acehitbox.bmp", 0, 0, 0, 1, 1, 1, 1, 1, 1, 200, 200)); //TEMPORARY GET RID
}

Ace::~Ace()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}

void Ace::playAnimation()
{
	bool ended = false;
	if(eStance == eStand)
		animations[0]->playAnimation(x, y, 0, true, &ended);
	if(eStance == eRun)
		animations[1]->playAnimation(x, y, 0, true, &ended);
	if(eStance == eSlice)
	{
		animations[2]->playAnimation(x, y, 4, false, &ended);
		if(ended)
			eStance = eStand;
	}
	if(eStance == eJumpSlice)
	{
		animations[3]->playAnimation(x, y, 0, false, &ended);
		if(ended)
			eStance = eJump;
	}
	if(eStance == eJump)
		animations[4]->playAnimation(x, y, 0, true, &ended);
	if(eStance == eHurt)
		animations[5]->playAnimation(x, y, 0, true, &ended);
	//animations[6]->playAnimation(x, y); // TEMPORARY GET RID
}

void Ace::setAnimation(Ace::eAnimation animation)
{
	if(eStance != eStand)
		animations[0]->stopAnimation();
	if(eStance != eRun)
		animations[1]->stopAnimation();
	if(eStance != eSlice)
		animations[2]->stopAnimation();
	if(eStance != eJumpSlice)
		animations[3]->stopAnimation();
	if(eStance != eJump)
		animations[4]->stopAnimation();
	if(eStance != eHurt)
		animations[5]->stopAnimation();

	eStance = animation;
}

// set which way he is facing (True -> Right, False -> Left)
void Ace::changeDirection()
{
	facingRight = !facingRight;
	for (int i = 0; i < animations.size(); i++)
		animations[i]->flipAnimation();
}

bool Ace::getFacingRight() { return facingRight;}

// let gravity affect Ace's fall
void Ace::aceGravity(double gravity)
{
	aceFall += gravity;
}

bool Ace::getFlying(){return flying;}

void Ace::setFall(double fall)
{
	aceFall = fall;

	// if Ace's fall is negative (he's going up) set flying to true
	if(fall < 0)
		flying = true;
}
double Ace::getFall(){ return aceFall;}
int Ace::getSpeed(){ return aceSpeed;}

void Ace::move(int x, int y, Map *map)
{
	Ace::x += x;
	while(map->checkAceHitBox((RectangleObject)*this))
	{
		if(x > 0)
			Ace::x -= 1;
		else
			Ace::x += 1;
	}

	if(y < 0)
		flying = true;
	Ace::y += y;

	while(map->checkAceHitBox((RectangleObject)*this))
	{
		if(y > 0)
			Ace::y -= 1;
		else
			Ace::y += 1;
		aceFall = 0;
		flying = false;
	}
}

bool Ace::checkStance(Ace::eAnimation stance)
{
	if(stance == eStance)
		return true;
	return false;
}
/* TEMPORARY
class Character
{
protected:
	hitBox body;
	hitBox weapon;
	vector<Animation> animations;

	void moveCharacter(int xShift, int yShift);
public:
	// Destructor
	virtual ~Character();
	
	// Virtual functions

	virtual void playAnimation() = 0;
	
};
*/