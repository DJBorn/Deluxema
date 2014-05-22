#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <vector>

#include "RectangleObject.h"
#include "Animation.h"
#include "Character.h"
#include "Sound.h"
#include "Ace.h"
#include "Map.h"

// Class for a generic character on the screen
class Robot : public Character
{
public:
	void initialize();

	// Constructor and Destructor
	Robot();
	~Robot();

	// enum for which animation he is in
	enum eAnimation {eStand, eRun, eDash, ePunch, eDie};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);

	void respawn();

	void move(int x, int y, Map *map);
	
	// Check if the given stance is Ace's current stance
	bool checkStance(eAnimation stance);

	void AI(Ace *ace, Map *map);
private:
	int dashDelay;
	int maxDashDelay;
	bool punched;

	int maxSpeed;

	int maxSpeedDuration;
	int maxSpeedTimer;

	int respawnTimer;
	int respawnDuration;
	bool speedingUp;

	Sound dashSound;
	Sound deathSound;

	eAnimation eStance;
};

#endif // _ROBOT_H_
