#ifndef _ACE_H_
#define _ACE_H_

#include <vector>

#include "RectangleObject.h"
#include "Animation.h"
#include "Character.h"

// Class for a generic character on the screen
class Ace : public Character
{
public:
	// Constructor and Destructor
	Ace(int x, int y);
	~Ace();

	// enum for which animation he is in
	enum eAnimation {eStand, eRun, eSlice, eJumpSlice};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);

	// set which way he is facing (True -> Right, False -> Left)
	void setDirection(bool right);

	void setFall(double fall);
	double getFall();
	int getSpeed();

	// Let gravity affect Ace's fall
	void aceGravity(double gravity);

	void move(int x, int y);
private:
	eAnimation eStance;
	bool facingRight;
	int aceSpeed;
	double aceFall;
};

#endif // _ACE_H_
