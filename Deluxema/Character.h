#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "RectangleObject.h"
#include "Animation.h"
#include <vector>

// Class for a generic character on the screen
class Character : public RectangleObject
{
protected:

	vector<Animation*> animations;
	Character();
	Character(int attackWidth, int attackHeight);
	
	bool attacking;
	RectangleObject attack;
	bool facingRight;
	double fall;
	bool flying;
	int speed;

public:

	// Destructor
	virtual ~Character();
	
	// Virtual functions
	virtual void playAnimation() = 0;

	// set which way he is facing (True -> Right, False -> Left)
	void changeDirection();

	bool getFacingRight();

	void setFall(double fall);
	
	// Let gravity affect the character's fall
	void Gravity(double gravity);

	RectangleObject getAttack();

	bool Attacking();
};

#endif // _CHARACTER_H_