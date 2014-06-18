#include "Map.h"
#include "DarkGDK.h"
#include "idAssigner.h"
#include "RectangleObject.h"

using namespace std;

// Map Constructor
Map::Map()
{
	xMap = 0;
	yMap = 0;
	// Get an id
	idMap = generateid();
	idMapBreached = generateid();

	// Backdrop for background
 	dbCreateAnimatedSprite (idMap, "includes//Sprites//Map//Ace_House.bmp", 1, 1, idMap);
 	dbCreateAnimatedSprite (idMapBreached, "includes//Sprites//Map//Ace_House_Breached.bmp", 1, 1, idMapBreached);
	dbScaleSprite(idMap, 200);
	dbScaleSprite(idMapBreached, 200);

	// Create a sprite for this image
	dbSprite ( idMap, xMap, yMap, idMap );
}

Map::~Map()
{
	dbDeleteSprite(idMap);
	dbDeleteSprite(idMapBreached);
	deleteid(idMap);
	deleteid(idMapBreached);
}

// Add a new global hit box 
void Map::addGlobalHitBox(int x, int y, int width, int height)
{
	RectangleObject newHitBox(x, y, width, height);
	globalHitBox.push_back(newHitBox);
}

// Add a new Player hit box
void Map::addAceHitBox(int x, int y, int width, int height)
{
	RectangleObject newHitBox(x, y, width, height);
	aceHitBox.push_back(newHitBox);
}

// hit detection for global hitbox
bool Map::checkGlobalHitBox(RectangleObject object)
{
		for(int i = 0; i < globalHitBox.size(); i++)
			if(globalHitBox[i].checkCollision(object))
				return true;
	return false;
}

// hit detection for ace hitbox
bool Map::checkAceHitBox(RectangleObject object)
{
		for(int i = 0; i < aceHitBox.size(); i++)
			if(aceHitBox[i].checkCollision(object))
				return true;

		for(int i = 0; i < globalHitBox.size(); i++)
			if(globalHitBox[i].checkCollision(object))
				return true;
	return false;
}

void Map::changeToNormal()
{
	// change the background back to its original state
	dbHideSprite(idMapBreached);
	dbShowSprite(idMap);
	dbSprite ( idMap, xMap, yMap, idMap );
}

void Map::changeToBreached()
{
	// change the background to breached
	dbHideSprite(idMap);
	dbShowSprite(idMapBreached);
	dbSprite ( idMapBreached, xMap, yMap, idMapBreached );
}