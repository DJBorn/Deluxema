#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "RectangleObject.h"
#include "Animation.h"
#include <vector>


class Missile  : public RectangleObject
{
public:
	Missile();
	~Missile();

	void initialize();
	
	// enum for which animation the Missile is in
	enum eAnimation {eFlying, eDestroyed};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);
	

private:
	eAnimation eState;
	vector<Animation*> animations;
};

#endif // _MISSILE_H_