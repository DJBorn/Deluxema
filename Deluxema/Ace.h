#ifndef _ACE_H_
#define _ACE_H_

#include <vector>

#include "RectangleObject.h"
#include "Animation.h"
#include "Character.h"
#include "Map.h"

// Class for a generic character on the screen
class Ace : public Character
{
public:
	// Constructor and Destructor
	Ace(int x, int y);
	~Ace();

	// enum for which animation he is in
	enum eAnimation {eStand, eRun, eSlice, eJumpSlice, eJump, eHurt};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);

	// set which way he is facing (True -> Right, False -> Left)
	void changeDirection();

	// check if he is facing right
	bool getFacingRight();

	void setFall(double fall);
	double getFall();
	int getSpeed();
	bool getFlying();
	// Let gravity affect Ace's fall
	void aceGravity(double gravity);

	void move(int x, int y, Map *map);
	
	// Check if the given stance is Ace's current stance
	bool checkStance(eAnimation stance);
private:
	int leftConstant;
	eAnimation eStance;
	bool facingRight;
	int aceSpeed;
	double aceFall;
	bool flying;
};

#endif // _ACE_H_
