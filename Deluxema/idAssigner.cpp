#include "idAssigner.h"

static bool idList[500] = { false };

int generateid()
{
	int i = 1;
	while(idList[i] && i < 500)
		i++;

	idList[i] = true;
	return i;
}

void deleteid(int id)
{
	idList[id] = false;
}

