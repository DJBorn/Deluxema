#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>

using namespace std;

class Animation
{
public:
	Animation(char* path, int x, int y, int flip, int width, int height, int startFrame,
			  int curFrame, int maxFrame, int maxDelay, int priority, int scale);
	~Animation();
	
	void playAnimation(int x, int y, int eventFrame, bool repeat, bool *ended);
	void stopAnimation();
	void flipAnimation();

private:
	int x;
	int y;
	int flip;
	string path;
	int startFrame;
	int curFrame;
	int maxFrame;
	int delay;
	int maxDelay;
	int id;
	bool flipped;
};

#endif // _ANIMATION_H_