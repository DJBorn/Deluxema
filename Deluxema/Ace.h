#ifndef _ACE_H_
#define _ACE_H_

#include <vector>

#include "HitBox.h"
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
	void setAnimation(eAnimation animation);
	void moveCharacter(int xShift, int yShift);

	void temp(int x, int y);
private:
	eAnimation eStance;
};

#endif // _ACE_H_


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