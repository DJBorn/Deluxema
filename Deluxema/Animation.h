#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>

using namespace std;

class Animation
{
public:
	Animation(char* path, int width, int height, int startFrame,
			  int curFrame, int maxFrame, int maxDelay, int priority, int scale);
	~Animation();
	
	void playAnimation(int x, int y);
	void stopAnimation();

private:
	string path;
	int startFrame;
	int curFrame;
	int maxFrame;
	int delay;
	int maxDelay;
	int id;
};

#endif // _ANIMATION_H_