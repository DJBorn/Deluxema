#include "Missile.h"
#include "idAssigner.h"
#include "DarkGDK.h"

Missile::Missile()
{
	id = generateid();
	dbCreateAnimatedSprite(id,"includes//Sprites//Missile//Missile.bmp", 4, 1, id);

	// scale the sprite
	dbScaleSprite(id, 200);
	// set the sprite priority
	dbSetSpritePriority(id, 200);
	// initially hide the sprite till called to play
	dbHideSprite(id);
}

Missile::~Missile()
{
	// delete the sprite and the id
	dbDeleteSprite(id);
	deleteid(id);
}