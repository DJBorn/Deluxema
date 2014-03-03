#include "DarkGDK.h"
#include "Input.h"

//player input

bool checkLeft( void )
{
	if ( dbKeyState ( 203 ) )
		return true;
	return false;
}

// check if the player presses the right key
bool checkRight( void )
{
	if ( dbKeyState ( 205 ) )
		return true;
	return false;
}

// check if the player presses the down key
bool checkDown ( void )
{
	if( dbDownKey ( ) )
		return true;
	return false;
}

// check if the player presses the up key
bool checkUp ( void )
{
	if( dbUpKey ( ) )
		return true;
	return false;
}

// check if the player presses Z (Jump)
bool checkJump ( void )
{
	if(dbKeyState ( 44 ))
		return true;
	return false;
}

// check if the player presses X (Slice)
bool checkSlice ( void )
{
	if(dbKeyState ( 45 ))
		return true;
	return false;
}

// check if the player presses the enter key
bool checkEnter ( void )
{
	if ( dbKeyState ( 28 ) )
		return true;
	return false;
}

