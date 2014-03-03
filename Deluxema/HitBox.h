#ifndef _HITBOX_H_
#define _HITBOX_H_

struct hitBox
{
	int x;
	int y;
	int width;
	int height;
};

bool checkCollision(hitBox target, hitBox object);

#endif // _HITBOX_H_