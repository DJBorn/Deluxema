#include "DarkGDK.h"
#include "Number.h"
#include "idAssigner.h"
#include <math.h>
#include <vector>

std::vector<int> id;

void createNumbers(int n)
{
	for(int i = 0; i < n; i++)
	{	
		id.push_back(generateid());
		// load the sprite
		dbCreateAnimatedSprite(id.back(), "includes//Sprites//Effects//Numbers.bmp", 10, 1, id.back());
		// scale the sprite
		dbScaleSprite(id.back(), 100);
		// set the sprite priority
		dbSetSpritePriority(id.back(), 202);
		// initially hide the sprite till called to play
		dbHideSprite(id.back());

	}
}

void displayNumber(int n, int x, int y)
{
	std::vector<int> number;

	// determine the number of digits in the number
	int digits = 0;
	int i = n;
	while(i)
	{
		digits++;
		i /= 10;
	}

	// hide the number sprites initially
	for(int i = 0; i < id.size(); i++)
	{
		dbHideSprite(id.at(i));
	}

	for(int i = 0; i < digits; i++)
	{
		number.push_back(n % 10);
		n /= 10;
	}

	int shift = 0;
	int index = 0;
	for(int i = number.size() - 1; i >= 0; i--)
	{
		dbShowSprite(id.at(index));
		dbSetSpriteFrame(id.at(index), number.at(i) + 1);
		dbSprite(id.at(index), x + shift, y, id.at(index));
		shift += dbSpriteWidth(id.at(index))/10;
		index++;
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
