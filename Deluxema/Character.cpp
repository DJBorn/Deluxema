#include <vector>

#include "DarkGDK.h"
#include "Character.h"

using namespace std;

Character::Character(){}

Character::Character(int attackWidth, int attackHeight) : attack(0, 0, attackWidth, attackHeight)
{ 
	flying = false;
	facingRight = true;
	attacking = false;
	fall = 0;
}

// Destructor
Character::~Character(){}

// set which way he is facing (True -> Right, False -> Left)
void Character::changeDirection()
{
	facingRight = !facingRight;
	for (int i = 0; i < animations.size(); i++)
		animations[i]->flipAnimation();
}

bool Character::getFacingRight()
{
	return facingRight;
}

// let gravity affect the character's fall
void Character::Gravity(double gravity)
{
	fall += gravity;
}

void Character::setFall(double fall)
{
	Character::fall = fall;

	// if the character's fall is negative (he's going up) set flying to true
	if(fall < 0)
		flying = true;
}

RectangleObject Character::getAttack()
{
	return attack;
}


bool Character::Attacking()
{
	return attacking;
}