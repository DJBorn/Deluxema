#include <vector>

// local functions
#include "RectangleObject.h"
#include "Animation.h"
#include "Map.h"
#include "Ace.h"
#include "Sound.h"
#include <vld.h>
using namespace std;

// Position and create his attacks when Ace is created
Ace::Ace(int x, int y) : Character(88, 76)
{
	speed = 5; //speed is 5

	Ace::x = x;
	Ace::y = y;
	eStance = eStand;


	width = 28;
	height = 74;


	// add all of Ace's animations
								//x, y, flip, width, height, startFrame, maxFrame, maxDelay, priority, scale
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Stand.bmp", -20, -12, -34, 4, 2, 0, 8, 8, 200, 200)); // delay is 6
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Run.bmp",  -62, -14, 50, 5, 2, 0, 10, 3, 200, 200)); // delay is 3
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Slice.bmp", -86, -30, -26, 5, 2, 0, 10, 2, 200, 200));// delay is 2
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Jump_Slash.bmp", -108, -30, 18, 3, 3, 0, 9, 2, 200, 200)); // delay is 2
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Jump.bmp", -58, 0, 50, 1, 1, 0, 1, 1, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Hurt.bmp", -34, -24, -2, 1, 1, 0, 1, 1, 200, 200));
	animations.push_back(new Animation("includes//Sprites//Ace//acehitbox.bmp", 0, 0, 0, 1, 1, 0, 1, 1, 200, 200)); //TEMPORARY GET RID
	animations.push_back(new Animation("includes//Sprites//Ace//Ace_Ground_Slash.bmp", 0, 0, 0, 1, 1, 0, 1, 1, 199, 200)); //TEMPORARY GET RID
}

Ace::~Ace()
{
	for(int i = 0; i < animations.size(); i++)
		delete animations[i];
}

void Ace::playAnimation()
{
	bool ended = false;
	int frame = -1;
	if(eStance == eStand)
		animations[0]->playAnimation(x, y, &frame, true, &ended);
	if(eStance == eRun)
		animations[1]->playAnimation(x, y, &frame, true, &ended);
	if(eStance == eSlice)
	{
		animations[2]->playAnimation(x, y, &frame, false, &ended);
		// If this animation started, play the slice sound
		if(frame == 1)
			playAceSlice();

		// If this reaches his attacking frame, activate his slice attack
		if(frame == 4)
		{
			attacking = true;
			int addFlip = 0;

			// reposition Ace's slice hit box
			if(!facingRight)
				addFlip = -160;
			attack.x = x + 50 + addFlip;
			attack.y = y - 10;

			//animations[7]->playAnimation(attack.x, attack.y, &frame, true, &ended); // TEMPORARY GET RID	
		}
		else
			attacking = false;

		// When this animation ends, Ace is standing
		if(ended)
		{
			setAnimation(eStand);
			animations[0]->playAnimation(x, y, &frame, true, &ended);
		}
	}
	if(eStance == eJumpSlice)
	{
		animations[3]->playAnimation(x, y, &frame, false, &ended);
		if(frame == 1)
			playAceSlice();

		// If this reaches his attacking frame, activate his slice attack
		if(frame == 4)
		{
			attacking = true;
			int addFlip = 0;

			// reposition Ace's slice hit box
			if(!facingRight)
				addFlip = -116;
			attack.x = x + 28 + addFlip;
			attack.y = y - 12;

			//animations[7]->playAnimation(attack.x, attack.y, &frame, true, &ended); // TEMPORARY GET RID	
		}
		else
			attacking = false;

		if(ended)
		{
			setAnimation(eJump);
			animations[4]->playAnimation(x, y, &frame, true, &ended);
		}
	}
	if(eStance == eJump)
		animations[4]->playAnimation(x, y, &frame, true, &ended);
	if(eStance == eHurt)
		animations[5]->playAnimation(x, y, &frame, true, &ended);
	//animations[6]->playAnimation(x, y, &frame, true, &ended); // TEMPORARY GET RID
}

void Ace::setAnimation(Ace::eAnimation animation)
{
	eStance = animation;
	if(eStance != eStand)
		animations[0]->stopAnimation();
	if(eStance != eRun)
		animations[1]->stopAnimation();
	if(eStance != eSlice)
		animations[2]->stopAnimation();
	if(eStance != eJumpSlice)
		animations[3]->stopAnimation();
	if(eStance != eJump)
		animations[4]->stopAnimation();
	if(eStance != eHurt)
		animations[5]->stopAnimation();
	//if(!groundSlicing)
		//animations[7]->stopAnimation(); // TEMPORARY CALIBRATION ANIMATION

}


void Ace::move(int x, int y, Map *map)
{
	Ace::x += x;
	while(map->checkAceHitBox((RectangleObject)*this))
	{
		if(x > 0)
			Ace::x -= 1;
		else
			Ace::x += 1;
	}

	if(y < 0)
	{
		flying = true;
	}
	Ace::y += y;

	while(map->checkAceHitBox((RectangleObject)*this))
	{
		if(flying)
			stopAceSlice();
		if(y > 0)
			Ace::y -= 1;
		else
			Ace::y += 1;
		fall = 0;
		flying = false;
	}
}

void Ace::checkHurt(vector<RectangleObject> attacks, vector<bool> attackerFacingRight, vector<bool> attacking)
{
	if(eStance != eHurt)
	{
		for(int i = 0; i < attacks.size(); i++)
		{
			if(checkCollision(attacks.at(i)) && attacking.at(i))
			{
				setAnimation(eHurt);
				if(!attackerFacingRight.at(i))
					hurtSpeed = -6;
				else
					hurtSpeed = 6;
				setFall(-10);
			}
		}
	}
}

void Ace::controlAce(Map *map,  bool jumpButton, bool sliceButton, bool leftButton, bool rightButton)
{
	/* Some of the logic in this function may look like it could be optimized but evertime
	   setAnimation() is called, it resets all the other animations, so we must stay consistent
	   with one animation at a time */

	int aceHorizontalMove = 0;

	if(!flying && eStance == eHurt)
	{
		setAnimation(eStand);
	}
	// ace cannot move while hurt
	if(eStance == eHurt)
	{
		aceHorizontalMove = hurtSpeed;
	}

	else
	{
		// if ace was commanded to jump while on the ground, make him jump
		if(jumpButton && !flying && eStance != eSlice)
		{
			playAceJump();
			setFall(-18);
		}
		
		// _____ANIMATIONS SET HERE_____

		// if ace was commanded to slice on the ground, or is already doing a slice, do a stand slice
		if(!flying && sliceButton || eStance == eSlice)
		{
			setAnimation(eSlice);
		}

		// if ace was commanded to slice in the air, do an air slice. Or continue if he was already doing one
		else if((sliceButton || eStance == eJumpSlice) && flying )
		{
			setAnimation(eJumpSlice);
		}

		// if ace was commanded to move right or left, set the animation to run, or jump if he's flying
		else if(rightButton || leftButton)
		{
			// make sure he's not attacking
			attacking = false;

			setAnimation(eRun);

			// if he's in the air, then set the animation to jump
			if(flying)
				setAnimation(eJump);
		}
		else
		{	
			// make sure he's not attacking
			attacking = false;

			// if no commands are given, set the animation to stand, or jump if he's flying
			setAnimation(eStand);
			if(flying)
				setAnimation(eJump);
		}

		// _____ANIMATION SET STOPS HERE_____

		// adjust ace's speed according to left and right commands
		if(rightButton)
		{
			if(eStance != eSlice)
			{
				// if he's not facing right and he's moving right, change his direction
				if(!facingRight && eStance != eJumpSlice)
					changeDirection();
				aceHorizontalMove = speed;
			}
		}	
		else if(leftButton)
		{
			if(eStance != eSlice)
			{
				// if he's facing right and he's moving left, change his direction
				if(facingRight && eStance != eJumpSlice)
					changeDirection();
				aceHorizontalMove = speed * -1;
			}
		}
	}

	// play ace's animation
	playAnimation();

	// move ace on the map
	move(aceHorizontalMove, fall, map);
}