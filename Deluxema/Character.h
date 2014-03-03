#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "HitBox.h"
#include "Animation.h"
#include <vector>

// Class for a generic character on the screen
class Character
{
protected:
	int x;
	int y;
	hitBox body;
	hitBox weapon;
	vector<Animation*> animations;

	void moveCharacter(int xShift, int yShift);
public:
	// Destructor
	virtual ~Character();
	
	// Virtual functions
	virtual void playAnimation() = 0;

	
};

#endif // _CHARACTER_H_