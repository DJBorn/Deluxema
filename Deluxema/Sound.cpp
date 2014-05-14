#include "DarkGDK.h"
#include "idAssigner.h"

int aceJumpId;
int aceSliceId;
int mainThemeId;

void SoundSetup()
{
	aceJumpId = generateid();
	aceSliceId = generateid();
	mainThemeId = generateid();
	dbLoadSound ( "includes//Sounds//Effects//Ace//Ace_Jump.wav" , aceJumpId );
	dbLoadSound ( "includes//Sounds//Effects//Ace//Ace_Slice.wav" , aceSliceId );
	dbLoadMusic ( "includes//Sounds//Music//Memeshikute.mp3" , mainThemeId );

	dbSetSoundVolume(aceSliceId, 90);
	dbSetMusicVolume(mainThemeId, 1);
}

void playAceJump()
{
	dbPlaySound(aceJumpId);
}

void playAceSlice()
{
	dbPlaySound(aceSliceId);
}

void stopAceSlice()
{
	dbStopSound(aceSliceId);
}

void playMainTheme()
{
	//dbLoopMusic(mainThemeId);
}


void deleteSounds()
{
	dbDeleteSound(aceJumpId);
	dbDeleteSound(aceSliceId);
	dbDeleteMusic(mainThemeId);
	deleteid(aceJumpId);
	deleteid(aceSliceId);
	deleteid(mainThemeId);
}