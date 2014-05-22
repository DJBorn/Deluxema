#include "DarkGDK.h"
#include "idAssigner.h"
#include "Sound.h"

Sound::Sound(char* path, int volume)
{
	Sound::volume = volume;
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

