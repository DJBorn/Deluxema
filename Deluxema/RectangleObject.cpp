#include "RectangleObject.h"

RectangleObject::RectangleObject() : width(0), height(0)
{
	x = 0; y = 0;
}

RectangleObject::RectangleObject(int x, int y, int width, int height)
{
	RectangleObject::width = width;
	RectangleObject::height = height;
	RectangleObject::x = x;
	RectangleObject::y = y;
}

RectangleObject::~RectangleObject(){}

bool RectangleObject::checkCollision(RectangleObject target)
{
	int RightEdge = x + width;
	int LeftEdge = x;
	int TopEdge = y;
	int BottomEdge = y + height;

	int targetRightEdge = target.x + target.width;
	int targetLeftEdge = target.x;
	int targetTopEdge = target.y;
	int targetBottomEdge = target.y + target.height;

	// check for collision
	return ((RightEdge >= targetLeftEdge && LeftEdge <= targetRightEdge) &&
	        (BottomEdge >= targetTopEdge && TopEdge <= targetBottomEdge));
}