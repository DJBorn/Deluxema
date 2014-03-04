#include "Map.h"
#include "DarkGDK.h"
#include "idAssigner.h"
#include "hitBox.h"

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
	hitBox newHitBox;

	newHitBox.x = x;
	newHitBox.y = y;
	newHitBox.width = width;
	newHitBox.height = height;

	globalHitBox.push_back(newHitBox);
}

// Add a new Player hit box
void Map::addAceHitBox(int x, int y, int width, int height)
{
	hitBox newHitBox;

	newHitBox.x = x;
	newHitBox.y = y;
	newHitBox.width = width;
	newHitBox.height = height;

	aceHitBox.push_back(newHitBox);
}

// hit detection for global hitbox
bool Map::checkGlobalHitBox(hitBox object)
{
		for(int i = 0; i < globalHitBox.size(); i++)
		{
			if(checkCollision(globalHitBox[i], object))
				return true;
		}
	return false;
}