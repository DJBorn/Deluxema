#include "DarkGDK.h"
#include "idAssigner.h"

int mainThemeId;
int startThemeId;
void MusicSetup()
{
	mainThemeId = generateid();
	startThemeId = generateid();
	dbLoadMusic("includes//Sounds//Music//MC Hotdog - Wo Ai Tai Mei.mp3", startThemeId);
	dbLoadMusic ( "includes//Sounds//Music//Memeshikute.mp3" , mainThemeId );

	dbSetMusicVolume(mainThemeId, 60);
	dbSetMusicVolume(startThemeId, 60);
}

void playStartTheme()
{
	dbLoopMusic(startThemeId);
}

void stopStartTheme()
{
	dbStopMusic(startThemeId);
}

void playMainTheme()
{
	dbLoopMusic(mainThemeId);
}

void deleteMusic()
{
	dbDeleteMusic(mainThemeId);
	dbDeleteMusic(startThemeId);
	deleteid(mainThemeId);
	deleteid(startThemeId);
}