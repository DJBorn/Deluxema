#ifndef _RECTANGLEOBJECT_H_
#define _RECTANGLEOBJECT_H_

#include "Object.h"

class RectangleObject : public Object
{
public:
	int width;
	int height;
	RectangleObject();
	RectangleObject(int x, int y, int width, int height);
	~RectangleObject();
	bool checkCollision(RectangleObject target);
};

#endif // _RECTANGLEOBJECT_H_