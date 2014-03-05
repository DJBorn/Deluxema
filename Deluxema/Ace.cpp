#include <vector>

// local functions
#include "RectangleObject.h"
#include "Animation.h"
#include "Ace.h"

using namespace std;

Ace::Ace(int x, int y)
{
	aceSpeed = 3;
	aceFall = 0;

	Ace::x = x;
	Ace::y = y;
	eStance = eStand;

	width = 28;
	height = 74;

	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Stand.bmp", 4, 2, 1, 1, 8, 6, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Run.bmp", 5, 2, 1, 1, 10, 3, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Slice.bmp", 5, 2, 1, 1, 10, 2, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Jump_Slash.bmp", 3, 3, 1, 1, 9, 2, 200, 200));
	animations.push_back(new Animation("includes//Sprites//acehitbox.bmp", 1, 1, 1, 1, 1, 1, 200, 200)); //TEMPORARY GET RID
}

Ace::~Ace()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}

void Ace::playAnimation()
{
	if(eStance == eStand)
	{
		spriteX = x - 20;
		spriteY = y - 12;
		animations[0]->playAnimation(spriteX, spriteY);
	}
	if(eStance == eRun)
	{
		spriteX = x - 62;
		spriteY = y - 14;
		animations[1]->playAnimation(spriteX, spriteY);
	}
	if(eStance == eSlice)
	{
		spriteX = x - 86;
		spriteY = y - 30;
		animations[2]->playAnimation(spriteX, spriteY);
	}
	if(eStance == eJumpSlice)
	{
		spriteX = x - 108;
		spriteY = y - 30;
		animations[3]->playAnimation(spriteX, spriteY);
	}
	animations[4]->playAnimation(x, y);
}

void Ace::setAnimation(Ace::eAnimation animation)
{
	//for(int i = 0; i < animations.size(); i++)
		//animations[i]->stopAnimation();

	eStance = animation;

}

// set which way he is facing (True -> Right, False -> Left)
void Ace::setDirection(bool right){facingRight = right;}

// let gravity affect Ace's fall
void Ace::aceGravity(double gravity)
{
	aceFall += gravity;
}

void Ace::setFall(double fall){aceFall = fall;}
double Ace::getFall(){ return aceFall;}
int Ace::getSpeed(){ return aceSpeed;}

void Ace::move(int x, int y)
{
	Ace::x += x;
	Ace::y += y;
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