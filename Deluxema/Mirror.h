#ifndef _MIRROR_H_
#define _MIRROR_H_

#include "RectangleObject.h"
#include "Animation.h"
#include <vector>

// Class for a generic character on the screen
class Mirror : public RectangleObject
{
public:
	Mirror();
	~Mirror();
private:
	vector<Animation*> animations;

};

#endif // _MIRROR_H_