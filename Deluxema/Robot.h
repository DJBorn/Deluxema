#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <vector>

#include "RectangleObject.h"
#include "Animation.h"
#include "Character.h"
#include "Map.h"

// Class for a generic character on the screen
class Robot : public Character
{
public:
	// Constructor and Destructor
	Robot(int x, int y);
	~Robot();

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
	void robotGravity(double gravity);

	void move(int x, int y, Map *map);
	
	// Check if the given stance is Ace's current stance
	bool checkStance(eAnimation stance);
private:
	bool Punching;
	RectangleObject Punch;
	int leftConstant;
	eAnimation eStance;
	bool facingRight;
	int robotSpeed;
	double robotFall;
	bool flying;
};

#endif // _ROBOT_H_
