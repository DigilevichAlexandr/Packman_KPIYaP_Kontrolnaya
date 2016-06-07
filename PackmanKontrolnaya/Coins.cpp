#include "stdafx.h"
#include "Coins.h"

SDL_Rect* Coins::MakeCoins()
{
	SDL_Rect* coins = new SDL_Rect[11];

	coins[0].x = 100;
	coins[0].y = 73;
	coins[0].w = 4;
	coins[0].h = 4;

	coins[1].x = 20;
	coins[1].y = 20;
	coins[1].w = 4;
	coins[1].h = 4;

	coins[2].x = 20;
	coins[2].y = 116;
	coins[2].w = 4;
	coins[2].h = 4;

	coins[3].x = 20;
	coins[3].y = 286;
	coins[3].w = 4;
	coins[3].h = 4;

	coins[4].x = 124;
	coins[4].y = 416;
	coins[4].w = 4;
	coins[4].h = 4;

	coins[5].x = 416;
	coins[5].y = 286;
	coins[5].w = 4;
	coins[5].h = 4;

	coins[6].x = 312;
	coins[6].y = 414;
	coins[6].w = 4;
	coins[6].h = 4;

	coins[7].x = 416;
	coins[7].y = 20;
	coins[7].w = 4;
	coins[7].h = 4;

	coins[8].x = 416;
	coins[8].y = 112;
	coins[8].w = 4;
	coins[8].h = 4;

	coins[9].x = 340;
	coins[9].y = 73;
	coins[9].w = 4;
	coins[9].h = 4;

	coins[10].x = 218;
	coins[10].y = 160;
	coins[10].w = 4;
	coins[10].h = 4;

	return coins;
}

bool* Coins::MakeExistingFglags()
{
	bool* isCoinExist = new bool[11];

	for (int i = 0;i < 11;i++)
	{
		isCoinExist[i] = true;
	}

	return isCoinExist;
}

