
#include "Map.h"
#include "DarkGDK.h"
#include "idAssigner.h"

using namespace std;

// Map Constructor
Map::Map()
{
	// Get an id
	idMap = generateid();

	// Backdrop for background
 	dbCreateAnimatedSprite (idMap, "includes//Ace_House.bmp", 1, 1, idMap);

	// Create a sprite for this image
	dbSprite ( idMap, 0, 0, idMap );
}

Map::~Map()
{
	dbDeleteSprite(idMap);
	deleteid(idMap);
}