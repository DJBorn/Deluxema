#include "DarkGDK.h"
#include "idAssigner.h"

int mainThemeId;
int startThemeId;
int mainThemeVolume;
void MusicSetup()
{
	mainThemeVolume = 55;
	mainThemeId = generateid();
	startThemeId = generateid();
	dbLoadMusic("includes//Sounds//Music//MC Hotdog - Wo Ai Tai Mei.mp3", startThemeId);
	dbLoadMusic ( "includes//Sounds//Music//Memeshikute.mp3" , mainThemeId );

	dbSetMusicVolume(mainThemeId, mainThemeVolume);
	dbSetMusicVolume(startThemeId, 55);
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

void fadeMainTheme()
{
	mainThemeVolume -= 3;
	dbSetMusicVolume(mainThemeId, mainThemeVolume);
}

void resetMainThemeVolume()
{
	mainThemeVolume = 55;
	dbSetMusicVolume(mainThemeId, mainThemeVolume);
}

void deleteMusic()
{
	dbDeleteMusic(mainThemeId);
	dbDeleteMusic(startThemeId);
	deleteid(mainThemeId);
	deleteid(startThemeId);
}