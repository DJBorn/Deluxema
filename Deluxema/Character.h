#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "HitBox.h"
#include "Animation.h"
#include <vector>

// Class for a generic character on the screen
class Character
{
protected:
	int spriteX;
	int spriteY;

	hitBox body;
	hitBox weapon;
	vector<Animation*> animations;
	virtual void moveCharacter(int xShift, int yShift) = 0;


public:
	// Destructor
	virtual ~Character();
	
	// Virtual functions
	virtual void playAnimation() = 0;

	hitBox getBody();

	
};

#endif // _CHARACTER_H_