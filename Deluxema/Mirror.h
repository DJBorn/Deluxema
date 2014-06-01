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

private:
	int verticalDelay;		// the vertical delay counter
	int maxVerticalDelay;	// How often to move the mirror vertically
	int vUnitsShifted;		// The units shifted in each direction 0 being neutral, positive is upwards, negative is downwards
	bool shiftingUp;		// To state whether the Mirror is moving up or down
	eAnimation eState;		// Which animation it is in
	vector<Animation*> animations;

};

#endif // _MIRROR_H_