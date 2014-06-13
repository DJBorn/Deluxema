#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "RectangleObject.h"
#include "Animation.h"
#include "Explosion.h"
#include "Map.h"
#include <vector>


class Missile  : public RectangleObject
{
public:
	Missile();
	~Missile();

	void initialize();
	
	// enum for which animation the Missile is in
	enum eAnimation {eFlying, eDestroyed};

	// play an animation
	void playAnimation();

	// Set which animation to play
	void setAnimation(eAnimation animation);

	// set which way the Missile is facing (True -> Right, False -> Left)
	void changeDirection();

	void checkTargetCollision(RectangleObject target, bool *hit);

	void respawn();

	void checkHitCollision(RectangleObject object, bool attackerFacingRight, bool attacking, int &score);
	
	// move the missile
	void AI(Map *map);

	// apply gravity on missile
	void Gravity(double gravity);

	void playExplosion();
	

private:
	int speed;
	double fall;
	int maxSpeed;
	bool facingRight;
	Explosion explosion;
	Sound Explode;
	eAnimation eState;
	vector<Animation*> animations;
};

#endif // _MISSILE_H_