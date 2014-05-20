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
	enum eAnimation {eStand, eRun, ePunch, eDie};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);


	void move(int x, int y, Map *map);
	
	// Check if the given stance is Ace's current stance
	bool checkStance(eAnimation stance);
private:
	eAnimation eStance;
};

#endif // _ROBOT_H_
