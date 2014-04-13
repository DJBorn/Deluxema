#include "DarkGDK.h"
#include "idAssigner.h"

int aceJumpId;
int aceSliceId;

void SoundSetup()
{
	aceJumpId = generateid();
	aceSliceId = generateid();
	dbLoadSound ( "includes//Sounds//Effects//Ace//Ace_Jump.wav" , aceJumpId );
	dbLoadSound ( "includes//Sounds//Effects//Ace//Ace_Slice.wav" , aceSliceId );
}

void playAceJump()
{
	dbPlaySound(aceJumpId);
}

void playAceSlice()
{
	dbPlaySound(aceSliceId);
}


void deleteSounds()
{
	dbDeleteSound(aceJumpId);
	dbDeleteSound(aceSliceId);
	deleteid(aceJumpId);
	deleteid(aceSliceId);
}