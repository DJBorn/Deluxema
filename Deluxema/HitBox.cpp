#include "DarkGDK.h"
#include "HitBox.h"

using namespace std;

bool checkCollision(hitBox target, hitBox object)
{
	int objectRightEdge = object.x + object.width;
	int objectLeftEdge = object.x;
	int objectTopEdge = object.y;
	int objectBottomEdge = object.y + object.height;

	int targetRightEdge = target.x + target.width;
	int targetLeftEdge = target.x;
	int targetTopEdge = target.y;
	int targetBottomEdge = target.y + target.height;

	// check for collision
	return ((objectRightEdge >= targetLeftEdge && objectLeftEdge <= targetRightEdge) &&
	        (objectBottomEdge >= targetTopEdge && objectTopEdge <= targetBottomEdge));
}
/*
	int objectRightEdge = object.x + object.width;
	int objectLeftEdge = object.x;
	int objectTopEdge = object.y;
	int objectBottomEdge = object.y + object.height;

	int targetRightEdge = target.x + target.width;
	int targetLeftEdge = target.x;
	int targetTopEdge = target.y;
	int targetBottomEdge = target.y + target.height;

		// check if object collided from the top-right
	return (objectRightEdge >= targetLeftEdge || objectLeftEdge <= targetRightEdge) &&
	       (objectBottomEdge >= targetTopEdge || objectTopEdge <= targetBottomEdge);
*/