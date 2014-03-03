#ifndef _MAP_H_
#define _MAP_H_


#include <string>
#include <vector>
#include "HitBox.h"

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

	bool checkGlobalHitBox(hitBox object);
	
    private:
		int idMap;
		int xMap;
		int yMap;
		vector<hitBox> globalHitBox;
		vector<hitBox> aceHitBox;
};

#endif /* __MAP_H__ */