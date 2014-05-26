#include "DarkGDK.h"
#include "Number.h"
#include "idAssigner.h"
#include <math.h>

int id[4];

void createNumbers()
{
	for(int i = 0; i < 4; i++)
	{	
		id[i] = generateid();
		// load the sprite
		dbCreateAnimatedSprite(id[i], "includes//Sprites//Effects//Numbers.bmp", 10, 1, id[i]);
		// scale the sprite
		dbScaleSprite(id[i], 100);
		// set the sprite priority
		dbSetSpritePriority(id[i], 202);
		// initially hide the sprite till called to play
		dbHideSprite(id[i]);

	}
}

void displayNumber(int n, int x, int y)
{
	int number[4] = {-1 , -1, -1, -1};
	for(int i = 3; i >= 0; i--)
	{
		if(n != 0)
			number[i] = n % 10;
		n /= 10;
	}

	int shift = 0;
	for(int i = 0; i < 4; i++)
	{
		if(number[i] >= 0)
		{
			dbShowSprite(id[i]);
			dbSetSpriteFrame(id[i], number[i] + 1);
			dbSprite(id[i], x + shift, y, id[i]);
			shift += dbSpriteWidth(id[i])/10;
		}
		else
			dbHideSprite(id[i]);
	}
}
void deleteNumbers()
{
	for(int i = 0; i < 4; i++)
	{	
		// delete the sprite and give back the id
		dbDeleteSprite(id[i]);
		deleteid(id[i]);
	}

}
