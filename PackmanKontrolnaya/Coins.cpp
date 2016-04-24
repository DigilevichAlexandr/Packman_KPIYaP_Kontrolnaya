#include "Coins.h"

SDL_Rect* Coins::MakeCoins()
{
	SDL_Rect* coins = new SDL_Rect[1];

	coins[0].x = 100;
	coins[0].y = 73;
	coins[0].w = 4;
	coins[0].h = 4;
	
	return coins;
}

bool* Coins::MakeExistingFglags()
{
	bool* isCoinExist = new bool[1];

	isCoinExist[0] = true;

	return isCoinExist;
}

