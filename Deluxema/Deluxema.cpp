
#include "DarkGDK.h"
//#include "wtypes.h"

// Header Files
#include "Map.h"
#include "Input.h"
#include "Ace.h"
#include "Robot.h"
#include "RectangleObject.h"
#include "Music.h"
#include "Explosion.h"
#include "Number.h"
#include "Sound.h"
#include "idAssigner.h"
#include "Sparkle.h"
#include "Mirror.h"
#include "Missile.h"
#include <math.h>

using namespace std;

enum  eMode { eMapSetup, eGame, eTitleScreen };
eMode eGameMode = eMapSetup;

int timespeed = 0;
double gravity = 1;
int numRobots = 6;
int numMissiles = 2;
int score = 0;
int scoreId;
int titleId;
int startId;
int fadeId;
int fadeAlpha = 0;
bool fadeComplete = false;
int startSoundId;
int startDelay = 0;
int startFrame = 1;
int controlsId;
Explosion *leftExplosion, *rightExplosion;
Sparkle *sparkle1, *sparkle2, *sparkle3;
vector<Missile*>* missiles;


bool enteringGame = false;
int explosionTimer = 0;

// Variables

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

void createMenuEffects()
{
	scoreId = generateid();
	dbCreateAnimatedSprite(scoreId, "includes//Sprites//Effects//Score.bmp", 1, 1, scoreId);
	dbSprite(scoreId, 200, 0, scoreId);
	dbHideSprite(scoreId);
	dbSetSpritePriority(scoreId, 202);

	titleId = generateid();
	dbCreateAnimatedSprite(titleId, "includes//Sprites//Effects//Deluxema.bmp", 1, 1, titleId);
	dbSprite(titleId, 500 - dbSpriteWidth(titleId)/2, 68, titleId);
	dbSetSpritePriority(titleId, 202);

	startId = generateid();
	dbCreateAnimatedSprite(startId, "includes//Sprites//Effects//Start.bmp", 1, 2, startId);
	dbSprite(startId, 500 - dbSpriteWidth(startId)/2, 250, startId);
	dbSetSpritePriority(startId, 202);

	controlsId = generateid();
	dbCreateAnimatedSprite(controlsId, "includes//Sprites//Effects//Controls.bmp", 1, 1, controlsId);
	dbSprite(controlsId, 500 - dbSpriteWidth(controlsId)/2, 374, controlsId);
	dbSetSpritePriority(controlsId, 202);

	fadeId = generateid();
	dbCreateAnimatedSprite(fadeId, "includes//Sprites//Effects//Fade.bmp", 1, 1, fadeId);
	dbSprite(fadeId, 0, 0, fadeId);
	dbSetSpritePriority(fadeId, 300);
	dbSetSpriteAlpha(fadeId, 0);

	startSoundId = generateid();
	dbLoadSound("includes//Sounds//Effects//Start_Select.wav", startSoundId);
	dbSetSoundVolume(startSoundId, 90);
}
void deleteMenuEffects()
{
	dbDeleteSprite(titleId);
	dbDeleteSprite(startId);
	dbDeleteSprite(controlsId);
	dbDeleteSound(startSoundId);
	delete sparkle1;
	delete sparkle2;
	delete sparkle3;
}

void fadeOut()
{
	fadeAlpha+= 15;
	if(fadeAlpha > 255)
		fadeComplete = true;
	else
		dbSetSpriteAlpha(fadeId, fadeAlpha);

}

// Initial setup for the game
void setup()
{
	// when starting a Dark GDK program it is useful to set global
	// application properties, we begin by turning the sync rate on,
	// this means we control when the screen is updated, we also set
	// the maximum rate to 60 which means the maximum frame rate will
	// be set at 60 frames per second
	dbSyncOn();
	dbSyncRate ( 60 );

	// Get the screen resolution
	int horizontal;
	int vertical;
	GetDesktopResolution(horizontal, vertical);

	// Set window size
	const int windowX = 1000;
	const int windowY = 400;
	dbSetDisplayMode ( 1000, 400, 32 ); 

	// Center window
	dbSetWindowPosition ( horizontal/2 - windowX/2 , vertical/2 - windowY/2 );

	// a call is made to this function so we can stop the GDK from
	// responding to the escape key, we can then add in some code in our
	// main loop so we can control what happens when the escape key is pressed
	dbDisableEscapeKey ( );

	// now we will set the random seed value to the timer, this will
	// help us to get more random values each time we run the program
	dbRandomize ( dbTimer ( ) );

	// Transparent color
	dbSetImageColorKey ( 255, 0, 255 );

	createMenuEffects();

	// Setup all sounds
	MusicSetup();

	playStartTheme();
}



// Map setup creates all the hit boxes where the player and robots shouldn't go
void mapSetup(Map *map)
{
	map->addGlobalHitBox(-1000, 386, 3000, 50);
	map->addAceHitBox(-12, 0, 20, 500);
	map->addAceHitBox(992, 0, 20, 500);
	eGameMode = eTitleScreen;
}

void titleScreen(Ace *ace, Map *map, Mirror *mirror)
{
	// Hide game texts if the game is restarting
	dbHideSprite(scoreId);
	mirror->playAnimation();
	mirror->moveVertical();
	mirror->playAnimation();

	if(!enteringGame)
	{
		// make the start button blink
		startDelay++;
		if(startDelay == 30)
		{
			startDelay = 0;
			dbSetSpriteFrame(startId, (++startFrame % 2) + 1);
		}
		ace->setAnimation(Ace::eSleeping);

		// play each sparkle
		sparkle1->playSparkle();
		sparkle2->playSparkle();
		sparkle3->playSparkle();
	}
	if(checkEnter() && !enteringGame)
	{
		// reset the sparkles
		sparkle1->resetSparkle();
		sparkle2->resetSparkle();
		sparkle3->resetSparkle();

		// play the start button sound effect
		dbPlaySound(startSoundId);

		// hide the texts
		dbHideSprite(titleId);
		dbHideSprite(startId);
		dbHideSprite(controlsId);

		// stop the title theme
		stopStartTheme();

		enteringGame = true;

		// set Ace's animation to waking up
		ace->setAnimation(Ace::eWakingUp);
	}
	
	if(enteringGame)
	{
		if(ace->checkStance(Ace::eWakingUp))
		{
			// play the explosions and increment timer
			explosionTimer++;
			rightExplosion->turnOnExplosion();
			leftExplosion->turnOnExplosion();
			rightExplosion->playExplosion(0, 6, 150, 220);
			leftExplosion->playExplosion(994, 1000, 150, 220);
			ace->setAnimation(Ace::eWakingUp);
		}
		else if(ace->checkStance(Ace::eSitting))
		{
			// increment explosionTimer
			explosionTimer++;
			ace->setAnimation(Ace::eSitting);

			// play the explosion for 100 iterations
			if(explosionTimer < 120)
			{
				rightExplosion->playExplosion(0, 6, 150, 220);
				leftExplosion->playExplosion(994, 1000, 150, 220);
			}
			// finish off the remaining explosions and change the map without the side windows
			else if(explosionTimer < 150)
			{
				map->changeToBreached();
				rightExplosion->turnOffExplosion();
				leftExplosion->turnOffExplosion();
				rightExplosion->playExplosion(0, 3, 110, 146);
				leftExplosion->playExplosion(997, 1000, 110, 146);
			}
			// then switch to Ace getting up 
			else
			{
				ace->setAnimation(Ace::eGettingUp);
			}
		}
		else if(ace->checkStance(Ace::eGettingUp))
		{
			ace->setAnimation(Ace::eGettingUp);
		}
		else if(ace->checkStance(Ace::eGettingSword))
		{
			playMainTheme();
			ace->setAnimation(Ace::eGettingSword);
		}
		else
		{
			dbShowSprite(scoreId);
			eGameMode = eGame;
		}

	}
	ace->playAnimation();
}

void applyGravity(Ace *ace, vector<Robot*>* robots)
{
	ace->Gravity(gravity);
	for(int i = 0; i < robots->size(); i++)
	{
		robots->at(i)->Gravity(gravity/8);
	}
	for(int i = 0; i < missiles->size(); i++)
	{
		missiles->at(i)->Gravity(gravity/4);
	}
}

void controller(Ace *ace, vector<Robot*>* robots, Map *map)
{
	vector<RectangleObject> robotAttacks;
	vector<bool> attackerFacingRight;
	vector<bool> attacking;
	for(int i = 0; i < robots->size(); i++)
	{
		robotAttacks.push_back(robots->at(i)->getAttack());
		attackerFacingRight.push_back(robots->at(i)->getFacingRight());
		attacking.push_back(robots->at(i)->Attacking());
	}
	ace->checkHurt(robotAttacks, attackerFacingRight, attacking);
	ace->controlAce(map, checkZ(), checkX(), checkLeft(), checkRight());
}

void robotAI(vector<Robot*>* robots, Ace *ace, Map *map)
{
	for(int i = 0; i < robots->size(); i++)
	{
		robots->at(i)->checkDeath(ace->getAttack(), ace->getFacingRight(), ace->Attacking(), score);
		robots->at(i)->AI(ace, map);
	}
}

void mirrorAI(Mirror *mirror)
{
	mirror->moveVertical();
	mirror->moveHorizontal();
	mirror->playAnimation();
}

void missileAI(Ace *ace, Mirror *mirror, Map *map)
{
	for(int i = 0; i < missiles->size(); i++)
	{
		bool hit = false;
		missiles->at(i)->AI(map);
		missiles->at(i)->checkTargetCollision((RectangleObject)*mirror, &hit);
		if(hit)
			mirror->hit();
		missiles->at(i)->checkHitCollision(ace->getAttack(), ace->getFacingRight(), ace->Attacking(), score);
	}
}

void continuousAnimations(vector<Robot*>* robots)
{
	for(int i = 0; i < robots->size(); i++)
	{
		robots->at(i)->playExplosion();
	}
	for(int i = 0; i < missiles->size(); i++)
	{
		missiles->at(i)->playExplosion();
	}
}


void Deluxema(Map *map, Ace *ace, vector<Robot*>* robots, Mirror *mirror)
{
	// switch for game mode
	switch ( eGameMode )
	{
	case eMapSetup:
		{
			mapSetup(map);
			break;
		}
	case eTitleScreen:
		{
			titleScreen(ace, map, mirror);
			break;
		}
	case eGame:
		{	
			applyGravity(ace, robots);
			controller(ace, robots, map);
			robotAI(robots, ace, map);
			continuousAnimations(robots);
			missileAI(ace, mirror, map);
			mirrorAI(mirror);
			displayNumber(score, 286, 0);
			if(mirror->Destroyed())
			{
				timespeed = 15;
				fadeOut();
			}
			break;
		}
	}
}


// the main entry point for the application is this function
void DarkGDK ( void )
{
	// Get the basic setup done
	setup();

	// Create objects
	Map *map = new Map();
	Ace *ace = new Ace(484, 311);
	Mirror *mirror = new Mirror(500 - 34, 146);
	vector<Robot*>* robots = new vector<Robot*>;
	for(int i = 0; i < numRobots; i++)
	{
		robots->push_back(new Robot());
	}
	
	missiles = new vector<Missile*>;
	for(int i = 0; i < numMissiles; i++)
	{
		missiles->push_back(new Missile());
	}

	leftExplosion = new Explosion();
	rightExplosion = new Explosion();
	createNumbers(4);
	sparkle1 = new Sparkle(230, 30, 100);
	sparkle2 = new Sparkle(400, 70, 200);
	sparkle3 = new Sparkle(600, 40, 150);


	int time = 0;
	// Main Dark GDK loop
	while ( LoopGDK ( ) )
	{
		time++;
			if(time > timespeed)
			{
				time = 0;
				Deluxema(map, ace, robots, mirror);
			}

		// exit if escape key is pressed
		if ( dbEscapeKey ( ) )
			break;

		// update the contents of the screen
		dbSync ( );
	}

	// Delete objects
	deleteMenuEffects();
	delete leftExplosion;
	delete rightExplosion;
	deleteNumbers();
	for(int i = 0; i < robots->size(); i++)
	{
		delete robots->at(i);
	}
	for(int i = 0; i < missiles->size(); i++)
	{
		delete missiles->at(i);
	}
	delete robots;
	delete mirror;
	delete map;
	delete ace;
	deleteMusic();

	return;
}