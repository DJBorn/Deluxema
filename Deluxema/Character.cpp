#include <vector>

#include "DarkGDK.h"
#include "Character.h"

using namespace std;

// Destructor
Character::~Character(){}

hitBox Character::getBody()
{
	return body;
}