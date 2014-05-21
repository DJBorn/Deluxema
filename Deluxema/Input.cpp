#include "DarkGDK.h"
#include "Input.h"

//player input

bool z = false;
bool x = false;

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
	if( dbDownKey ( ))
	{

		return true;
	}
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
bool checkZ ( void )
{
	if(dbKeyState ( 44 ))
	{
		if(z)
			return false;
		z = true;
		return z;
	}
	z = false;
	return z;
}

// check if the player presses X (Slice)
bool checkX ( void )
{
	if(dbKeyState ( 45 ))
	{
		if(x)
			return false;
		x = true;
		return x;
	}
	x = false;
	return x;
}

// check if the player presses the enter key
bool checkEnter ( void )
{
	if ( dbKeyState ( 28 ) )
		return true;
	return false;
}

