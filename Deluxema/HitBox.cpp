#include "DarkGDK.h"
#include "HitBox.h"

using namespace std;

bool checkCollision(hitBox target, hitBox object)
{
		// check if object collided from the top-right
		if(target.x <= object.x && object.x <= target.x + target.width &&
		   target.y + target.height >= object.y + object.height && object.y + object.height >= target.y)
			return true;
		// check if the object collided from the bottom left
		else if(target.x <= object.x && object.x <= target.x + target.width &&
				target.y <= object.y && object.y <= target.y + target.height)
			return true;
		// check if the object collided from the bottom left
		else if(target.x <= object.x + object.width && object.x + object.width <= target.x + target.width &&
				target.y <= object.y && object.y <= target.y + target.height)
			return true;
		// check if the object collided from the top left
		else if(target.x <= object.x + object.width && object.x + object.width <= target.x + target.width &&
				target.y + target.height >= object.y + object.height && object.y + object.height >= target.y)
			return true;
		return false;
}