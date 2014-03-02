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
	

    private:
		int idMap;
		vector<hitBox> GlobalhitBox;
		vector<hitBox> AcehitBox;
};

#endif /* __MAP_H__ */