#include <vector>

// local functions
#include "HitBox.h"
#include "Animation.h"
#include "Ace.h"

using namespace std;


Ace::Ace(int x, int y) 
{
	body.x = x;
	body.y = y;
	eStance = eStand;

	body.width = 28;
	body.height = 74;

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
		spriteX = body.x - 20;
		spriteY = body.y - 12;
		animations[0]->playAnimation(spriteX, spriteY);
	}
	if(eStance == eRun)
	{
		spriteX = body.x - 62;
		spriteY = body.y - 14;
		animations[1]->playAnimation(spriteX, spriteY);
	}
	if(eStance == eSlice)
	{
		spriteX = body.x - 86;
		spriteY = body.y - 30;
		animations[2]->playAnimation(spriteX, spriteY);
	}
	if(eStance == eJumpSlice)
	{
		spriteX = body.x - 108;
		spriteY = body.y - 30;
		animations[3]->playAnimation(spriteX, spriteY);
	}
	animations[4]->playAnimation(body.x, body.y);
}

void Ace::setAnimation(Ace::eAnimation animation)
{
	//for(int i = 0; i < animations.size(); i++)
		//animations[i]->stopAnimation();


	eStance = animation;

}

void Ace::moveCharacter(int xShift, int yShift)
{
	body.x += xShift;
	body.y += yShift;
}

void Ace::temp(int x, int y)
{
	body.x += x;
	body.y += y;
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