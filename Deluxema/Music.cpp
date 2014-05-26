#include "DarkGDK.h"
#include "idAssigner.h"

int mainThemeId;
void MusicSetup()
{
	mainThemeId = generateid();
	dbLoadMusic ( "includes//Sounds//Music//MC Hotdog - Wo Ai Tai Mei.mp3" , mainThemeId ); // Memeshikute

	dbSetMusicVolume(mainThemeId, 70);
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