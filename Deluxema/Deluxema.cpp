
#include "DarkGDK.h"
//#include "wtypes.h"


// Header Files
#include "Map.h"

using namespace std;

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
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// Get the screen resolution
	int horizontal;
	int vertical;
	GetDesktopResolution(horizontal, vertical);

	// Set window size
	const int windowX = 1000;
	const int windowY = 400;
	dbSetDisplayMode ( windowX, windowY, 32 ); 

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
}

// the main entry point for the application is this function
void DarkGDK ( void )
{
	setup();
	Map *map = new Map();

	// now we come to our main loop, we call LoopGDK so some internal
	// work can be carried out by the GDK
	while ( LoopGDK ( ) )
	{

		// here we check if the escape key has been pressed, when it has
		// we will break out of the loop
		if ( dbEscapeKey ( ) )
			break;

		// here we make a call to update the contents of the screen
		dbSync ( );
	}

	// delete all the sprites
	// delete the backdrop image
	delete map;


	return;
}













/*
class test
{
public:
	test()
	{
			for ( int i = 2; i < 30; i++ )
	{
		// create an animated sprite and give it the ID number from the
		// variable i, next is the filename, now we come to how many frames
		// across and down, in our case this is 4, finally we come to the image
		// ID that the sprite will use, again we use i
		dbCreateAnimatedSprite ( i, "sprite.bmp", 4, 4, i );

		// position our sprite at a random location
		dbSprite ( i, dbRnd ( 640 ), -dbRnd ( 1500 ), i );
	}
	}
		~test()
		{
		}
};
void DarkGDK ( void )
{
	// in this application a backdrop is loaded and then several
	// animated sprites are displayed on screen

	// when starting a Dark GDK program it is useful to set global
	// application properties, we begin by turning the sync rate on,
	// this means we control when the screen is updated, we also set
	// the maximum rate to 60 which means the maximum frame rate will
	// be set at 60 frames per second
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// a call is made to this function so we can stop the GDK from
	// responding to the escape key, we can then add in some code in our
	// main loop so we can control what happens when the escape key is pressed
	dbDisableEscapeKey ( );

	// now we will set the random seed value to the timer, this will
	// help us to get more random values each time we run the program
	dbRandomize ( dbTimer ( ) );

	// we are going to display a backdrop for the scene, to do this
	// we load our image and give it an ID number of 1, this particular
	// image is of a sky at night with stars

	// the next step is to create a sprite that uses this image, this
	// is achieved by calling dbSprite and passing in a value of 1 for the
	// sprites ID, 0 for the X coordinate, 0 for the Y coordinates and a
	// value of 1 for the image
	//dbSprite ( 1, 0, 0, 1 );

	// next we will load in some animated sprites, before doing this
	// we need to adjust the image color key, by using this function we
	// can make a specific color be transparent, in our case we want this
	// to be bright pink
	dbSetImageColorKey ( 255, 0, 255 );

	// in this loop we're going to create some animated sprites, the image
	// we load contains frames of animation for an asteroid

	test hey = new test();
	// now we come to our main loop, we call LoopGDK so some internal
	// work can be carried out by the GDK
	while ( LoopGDK ( ) )
	{
		// run a loop through all our sprites
		for ( int i = 2; i < 30; i++ )
		{
			// move the sprite down and play its animation
			// moving from frame 1 to 16 with a delay of 60 ms
			dbMoveSprite ( i, -2 );
			dbPlaySprite ( i, 1, 16, 60 );

			// check the position of the sprite, if it has gone off scren
			// then reposition it back to the top
			if ( dbSpriteY ( i ) > 500 )
				dbSprite ( i, dbRnd ( 640 ), -dbRnd ( 1500 ), i );
		}

		// here we check if the escape key has been pressed, when it has
		// we will break out of the loop
		if ( dbEscapeKey ( ) )
			break;

		// here we make a call to update the contents of the screen
		dbSync ( );
	}

	// when the user presses escape the code will break out to this location
	// and we can free up any previously allocated resources
	
	// delete all the sprites
	for ( int i = 1; i < 30; i++ )
		dbDeleteSprite ( i );

	// delete the backdrop image
	dbDeleteImage ( 1 );

	// and now everything is ready to return back to Windows
	return;
}
*/