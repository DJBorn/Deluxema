
#include "DarkGDK.h"
//#include "wtypes.h"


// Header Files
#include "Map.h"
#include "Input.h"
#include "Ace.h"
#include "Robot.h"
#include "RectangleObject.h"
#include "Sound.h"
#include <vld.h>

using namespace std;

enum  eMode { eMapSetup, eGame, eFiller };
eMode eGameMode = eMapSetup;

double gravity = 1;
int numRobots = 20;

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

	// Setup all sounds
	SoundSetup();

	playMainTheme();
}

// Map setup creates all the hit boxes where the player and robots shouldn't go
void mapSetup(Map *map)
{
	map->addGlobalHitBox(-1000, 386, 3000, 50);
	map->addAceHitBox(-12, 0, 20, 500);
	map->addAceHitBox(992, 0, 20, 500);
	eGameMode = eGame;
}

void applyGravity(Ace *ace, vector<Robot*>* robots)
{
	ace->Gravity(gravity);
	for(int i = 0; i < numRobots; i++)
	{
		robots->at(i)->Gravity(gravity/8);
	}
}
void controller(Ace *ace, Map *map)
{
	ace->controlAce(map, checkZ(), checkX(), checkLeft(), checkRight());
}

void robotAI(vector<Robot*>* robots, Ace *ace, Map *map)
{
	for(int i = 0; i < numRobots; i++)
	{
		robots->at(i)->AI(ace, map);
	}
}


void Deluxema(Map *map, Ace *ace, vector<Robot*>* robots)
{
	// switch for game mode
	switch ( eGameMode )
	{
	case eMapSetup:
		{
			mapSetup(map);
			for(int i = 0; i < 8; i++)
				ace->playAnimation();
			for(int i = 0; i < 12; i++)
			{
				for(int i = 0; i < numRobots; i++)
				{
					robots->at(0)->playAnimation();
				}
			}
			break;
		}
	case eGame:
		{	
			applyGravity(ace, robots);
			controller(ace, map);
			robotAI(robots, ace, map);
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
	Ace *ace = new Ace(50, 311);
	vector<Robot*>* robots = new vector<Robot*>;
	for(int i = 0; i < numRobots; i++)
	{
		robots->push_back(new Robot(10*(i+1), 291));
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
				Deluxema(map, ace, robots);
			}

		// exit if escape key is pressed
		if ( dbEscapeKey ( ) )
			break;

		// update the contents of the screen
		dbSync ( );
	}

	// Delete objects
	for(int i = 0; i < numRobots; i++)
	{
		delete robots->at(i);
	}
	delete robots;
	delete map;
	delete ace;
	deleteSounds();

	return;
}