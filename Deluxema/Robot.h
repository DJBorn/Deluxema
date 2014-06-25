#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <vector>

#include "RectangleObject.h"
#include "Animation.h"
#include "Character.h"
#include "Sound.h"
#include "Explosion.h"
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

	void checkDeath(RectangleObject attack, bool attackerFacingRight, bool attacking, int &score);

	void AI(RectangleObject *target, Map *map);

	void playExplosion();

	void playHitAnimation(RectangleObject target);

	// sound control
	void fadeSounds();
	void resetSounds();

	void resetExplosion();
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

	Explosion explosion;

	eAnimation eStance;

	Animation *hitAnimation;
	int hitAnimationX;
	int hitAnimationY;
	bool playingHitAnimation;
};

#endif // _ROBOT_H_
