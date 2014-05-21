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


	void move(int x, int y, Map *map);
	
	// Check if the given stance is Ace's current stance
	bool checkStance(eAnimation stance);

	// Control ace given the inputs
	void controlAce(Map *map, bool jumpButton, bool sliceButton, bool leftButton, bool rightButton);
private:
	eAnimation eStance;
};

#endif // _ACE_H_
