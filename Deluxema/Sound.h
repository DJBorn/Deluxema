#ifndef _SOUND_H_
#define _SOUND_H_

class Sound
{
public:
	Sound(char* path, int volume);
	~Sound();

	void playSound();
	void stopSound();
private:
	int id;
	int volume;
};


#endif // _SOUND_H_