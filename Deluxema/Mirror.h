#ifndef _MIRROR_H_
#define _MIRROR_H_

#include "RectangleObject.h"
#include "Animation.h"
#include <vector>

// Class for a generic character on the screen
class Mirror : public RectangleObject
{
public:
	Mirror(int x, int y);
	~Mirror();
	
	// enum for which animation the Mirror is in
	enum eAnimation {eMirror1, eMirror2, eMirror3, eMirror4, eMirror5, eMirrorBreak};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);

	// Move the Mirror vertically
	void moveVertical();
	void moveHorizontal();

private:
	int verticalDelay;			// the vertical delay counter
	int maxVerticalDelay;		// How often to move the mirror vertically
	int vUnitsShifted;			// The units shifted in each direction 0 being neutral, positive is upwards, negative is downwards
	bool shiftingUp;			// To state whether the Mirror is moving up or down
	eAnimation eState;			// Which animation it is in

	int horizontalMoveDelay;	// the counter for how often the mirror should move left or right
	int maxHorizontalMoveDelay;	// the maximum amount of time the mirror must wait before moving
	bool speedingUp;			// if the mirror is speeding up
	int curSpeed;				// the current speed of the mirror
	int maxSpeed;				// the maximum speed of the mirror when moving left and right
	int maxSpeedTimer;			// how long the mirror has been at max speed for
	int maxSpeedDuration;		// how long the mirror can be at its max speed for
	int horizontalDelay;		// the counter for the horizontal delay
	int maxHorizontalDelay;		// the horizontal delay counter which dictates how often the mirror should move one frame
	int hDashes;				// the position the mirror is in 0 being middle, positive is right and negative is left
	bool dashingRight;			// the state whether the mirror is moving left or right

	vector<Animation*> animations;

};

#endif // _MIRROR_H_