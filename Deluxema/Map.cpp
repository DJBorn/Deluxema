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

	// Backdrop for background
 	dbCreateAnimatedSprite (idMap, "includes//Sprites//Map//Ace_House.bmp", 1, 1, idMap);
	dbScaleSprite(idMap, 200);

	// Create a sprite for this image
	dbSprite ( idMap, xMap, yMap, idMap );
}

Map::~Map()
{
	dbDeleteSprite(idMap);
	deleteid(idMap);
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