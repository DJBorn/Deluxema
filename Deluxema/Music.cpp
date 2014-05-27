#include "DarkGDK.h"
#include "idAssigner.h"

int mainThemeId;
void MusicSetup()
{
	mainThemeId = generateid();
	dbLoadMusic ( "includes//Sounds//Music//Memeshikute.mp3" , mainThemeId ); // MC Hotdog - Wo Ai Tai Mei.mp3

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