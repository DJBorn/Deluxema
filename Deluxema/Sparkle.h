#ifndef _SPARKLE_H_
#define _SPARKLE_H_

#include "Object.h"

class Sparkle : public Object
{
public:
	Sparkle(int x, int y, int frequency);
	~Sparkle();

	void playSparkle();
private:
	int id;
	int frequency;
	int maxFrequency;
	int delay;
	int maxDelay;
	int frame;
	int maxFrame;
	bool glow;
};

#endif _SPARKLE_H_