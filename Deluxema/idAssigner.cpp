#include "idAssigner.h"

static bool idList[500] = { false };

// generate a new id
int generateid()
{
	// if an id is not taken within the list, return it
	int i = 1;
	while(idList[i] && i < 500)
		i++;

	idList[i] = true;
	return i;
}

// set the id as an open slot
void deleteid(int id)
{
	idList[id] = false;
}

