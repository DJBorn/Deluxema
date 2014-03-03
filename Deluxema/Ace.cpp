#include <vector>

// local functions
#include "HitBox.h"
#include "Animation.h"
#include "Ace.h"

using namespace std;


Ace::Ace(int x, int y) 
{
	Ace::x = x;
	Ace::y = y;
	animations.push_back(new Animation("includes//Ace_Stand.bmp", 4, 2, 1, 1, 8, 6, 200, 200));
}

Ace::~Ace()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}

void Ace::playAnimation()
{
	//for(int i = 0; i < animations.size(); i++)
		//animations[i].stopAnimation();
	//if(animation == eStand)
		animations[0]->playAnimation(x, y);
}

/* TEMPORARY
class Character
{
protected:
	int x;
	int y;
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