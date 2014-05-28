
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
#include "idAssigner.h"

using namespace std;

enum  eMode { eMapSetup, eGame, eTitleScreen };
eMode eGameMode = eMapSetup;

double gravity = 1;
int numRobots = 5;
int score = 0;
int scoreId;
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

	scoreId = generateid();
	dbCreateAnimatedSprite(scoreId, "includes//Sprites//Effects//Score.bmp", 1, 1, scoreId);
	dbSprite(scoreId, 200, 0, scoreId);
	dbSetSpritePriority(scoreId, 202);

	// Setup all sounds
	MusicSetup();

	playMainTheme();
}

// Map setup creates all the hit boxes where the player and robots shouldn't go
void mapSetup(Map *map)
{
	map->addGlobalHitBox(-1000, 386, 3000, 50);
	map->addAceHitBox(-12, 0, 20, 500);
	map->addAceHitBox(992, 0, 20, 500);
	eGameMode = eTitleScreen;
}

void titleScreen(Ace *ace, Map *map, Explosion *rightExplosion, Explosion *leftExplosion)
{
	if(!enteringGame)
		ace->setAnimation(Ace::eSleeping);
	if(checkEnter() && !enteringGame)
	{
		enteringGame = true;
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
			ace->setAnimation(Ace::eGettingSword);
		}
		else
			eGameMode = eGame;

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

void continuousAnimations(vector<Robot*>* robots)
{
	for(int i = 0; i < robots->size(); i++)
	{
		robots->at(i)->playExplosion();
	}
}


void Deluxema(Map *map, Ace *ace, vector<Robot*>* robots, Explosion *rightExplosion, Explosion *leftExplosion)
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
			titleScreen(ace, map, rightExplosion, leftExplosion);
			break;
		}
	case eGame:
		{	
			applyGravity(ace, robots);
			controller(ace, robots, map);
			robotAI(robots, ace, map);
			continuousAnimations(robots);
			displayNumber(score, 300, 0);
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
	vector<Robot*>* robots = new vector<Robot*>;
	Explosion *leftExplosion, *rightExplosion;
	leftExplosion = new Explosion();
	rightExplosion = new Explosion();
	createNumbers(4);

	for(int i = 0; i < numRobots; i++)
	{
		robots->push_back(new Robot());
	}
	

	int time = 0;
	int timespeed = 0;
	// Main Dark GDK loop
	while ( LoopGDK ( ) )
	{
		time++;
			if(time > timespeed)
			{
				time = 0;
				Deluxema(map, ace, robots, rightExplosion, leftExplosion);
			}

		// exit if escape key is pressed
		if ( dbEscapeKey ( ) )
			break;

		// update the contents of the screen
		dbSync ( );
	}

	// Delete objects
	
	delete leftExplosion;
	delete rightExplosion;
	deleteNumbers();
	for(int i = 0; i < robots->size(); i++)
	{
		delete robots->at(i);
	}
	delete robots;
	delete map;
	delete ace;
	deleteMusic();

	return;
}