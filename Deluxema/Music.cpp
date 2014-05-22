#include "DarkGDK.h"
#include "idAssigner.h"

int mainThemeId;
void MusicSetup()
{
	mainThemeId = generateid();
	dbLoadMusic ( "includes//Sounds//Music//Memeshikute.mp3" , mainThemeId );

	dbSetMusicVolume(mainThemeId, 20);
}

void playMainTheme()
{
	dbLoopMusic(mainThemeId);
}

void deleteMusic()
{
	dbDeleteMusic(mainThemeId);
	deleteid(mainThemeId);
}