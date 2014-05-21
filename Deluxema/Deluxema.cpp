
#include "DarkGDK.h"
//#include "wtypes.h"


// Header Files
#include "Map.h"
#include "Input.h"
#include "Ace.h"
#include "RectangleObject.h"
#include "Sound.h"
#include <vld.h>

using namespace std;

enum  eMode { eMapSetup, eGame, eFiller };
eMode eGameMode = eMapSetup;

double gravity = 1;

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
	map->addGlobalHitBox(0, 386, 1000, 50);
	map->addAceHitBox(-12, 0, 20, 500);
	map->addAceHitBox(992, 0, 20, 500);
	eGameMode = eGame;
}

void applyGravity(Ace *ace)
{
	ace->Gravity(gravity);
}
void controller(Ace *ace, Map *map)
{
	if(checkX())
		ace->controlAce(map, Ace::eSliceButton);
	else if(checkZ())
		ace->controlAce(map, Ace::eJumpButton);
	else if(checkLeft())
		ace->controlAce(map, Ace::eLeftButton);
	else if(checkRight())
		ace->controlAce(map, Ace::eRightButton);
	else
		ace->controlAce(map, Ace::eNoButton);
	
}
void Deluxema(Map *map, Ace *ace)
{
	// switch for game mode
	switch ( eGameMode )
	{
	case eMapSetup:
		{
			mapSetup(map);/*
				ace->setAnimation(ace->eRun);
				for(int i = 0; i < 24; i++)
					ace->playAnimation();
				ace->setAnimation(ace->eJump);
				for(int i = 0; i < 24; i++)
					ace->playAnimation();
				ace->setAnimation(ace->eJumpSlice);
				for(int i = 0; i < 24; i++)
					ace->playAnimation();
				ace->setAnimation(ace->eSlice);
				for(int i = 0; i < 24; i++)
					ace->playAnimation();*/
				ace->setAnimation(ace->eStand);
				for(int i = 0; i < 24; i++)
					ace->playAnimation();
						break;
		}
	case eGame:
		{	
			applyGravity(ace);
			controller(ace, map);
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
	

	int time = 0;
	int timespeed = 0;
	// Main Dark GDK loop
	while ( LoopGDK ( ) )
	{
		time++;
			if(time > timespeed)
			{
				time = 0;
				Deluxema(map, ace);
			}

		// exit if escape key is pressed
		if ( dbEscapeKey ( ) )
			break;

		// update the contents of the screen
		dbSync ( );
	}

	// Delete objects
	delete map;
	delete ace;
	deleteSounds();

	return;
}



/*
	PLAY SPRITES ALL ATLEAST ONCE BEFORE USING (weird buggy glitch that occurs only on first run of animations)

*/