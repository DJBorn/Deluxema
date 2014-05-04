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

public:

	// Destructor
	virtual ~Character();
	
	// Virtual functions
	virtual void playAnimation() = 0;

	
};

#endif // _CHARACTER_H_