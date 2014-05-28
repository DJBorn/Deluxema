#ifndef _MAP_H_
#define _MAP_H_


#include <string>
#include <vector>
#include "RectangleObject.h"

using namespace std;

class Map {
    public:
	// Constructor and Destructor.
	Map ();
	~Map ();
	
	// global hit box (any character can collide with it)
	void addGlobalHitBox(int x, int y, int width, int height);

	// Ace hit box (only Ace can collide with it; special player boundaries)
	void addAceHitBox(int x, int y, int width, int height);

	bool checkGlobalHitBox(RectangleObject object);
	bool checkAceHitBox(RectangleObject object);

	void changeToBreached();
	
    private:
		int idMap;
		int idMapBreached;
		int xMap;
		int yMap;
		vector<RectangleObject> globalHitBox;
		vector<RectangleObject> aceHitBox;
};

#endif /* __MAP_H__ */