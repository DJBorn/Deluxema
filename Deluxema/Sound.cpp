#include "DarkGDK.h"
#include "idAssigner.h"
#include "Sound.h"

Sound::Sound(char* path, int volume)
{
	Sound::volume = volume;
	fadeVolume = volume;
	id = generateid();
	dbLoadSound(path, id);
	dbSetSoundVolume(id, volume);
}

Sound::~Sound()
{
	dbDeleteSound(id);
	deleteid(id);
}

void Sound::playSound()
{
	dbPlaySound(id);
}

void Sound::stopSound()
{
	dbStopSound(id);
}

void Sound::fade()
{
	fadeVolume -= 8;
	if(fadeVolume < 0)
		fadeVolume = 0;
	dbSetSoundVolume(id, fadeVolume);
}

void Sound::resetVolume()
{
	fadeVolume = volume;
	dbSetSoundVolume(id, volume);
}
