#ifndef _RECTANGLEOBJECT_H_
#define _RECTANGLEOBJECT_H_

#include "Object.h"

class RectangleObject : public Object
{
	friend class Ace;
protected:
	int width;
	int height;
public:
	RectangleObject();
	RectangleObject(int x, int y, int width, int height);
	~RectangleObject();
	bool checkCollision(RectangleObject target);
};

#endif // _RECTANGLEOBJECT_H_