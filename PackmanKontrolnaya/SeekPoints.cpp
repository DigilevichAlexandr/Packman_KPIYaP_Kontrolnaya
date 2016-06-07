#include "stdafx.h"
#include "SeekPoints.h"

SDL_Rect* SeekPoints::MakeSeekPoints()
{
	SDL_Rect* points = new SDL_Rect[4];

	points[0].x = 15;
	points[0].y = 15;
	points[0].w = 44;
	points[0].h = 44;

	points[1].x = 415;
	points[1].y = 15;
	points[1].w = 44;
	points[1].h = 44;

	points[2].x = 415;
	points[2].y = 407;
	points[2].w = 44;
	points[2].h = 44;

	points[3].x = 15;
	points[3].y = 407;
	points[3].w = 44;
	points[3].h = 44;

	return points;
}