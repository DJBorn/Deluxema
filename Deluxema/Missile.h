#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "RectangleObject.h"


class Missile  : public RectangleObject
{
public:
	Missile();
	~Missile();
	

private:
	int id;
};

#endif // _MISSILE_H_