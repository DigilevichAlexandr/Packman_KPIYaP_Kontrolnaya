#include "Graphics.h"

Graphics::Graphics(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	TTF_Init();
}

Image* Graphics::NewImage(char* file)
{
	Image* image = new Image();
	image->surf = SDL_DisplayFormat(SDL_LoadBMP(file));

	return image;
}

Image* Graphics::NewImage(char* file, int r, int g, int b)
{
	Image* image = new Image();
	image->surf = SDL_DisplayFormat(SDL_LoadBMP(file));

	SDL_SetColorKey(image->surf, SDL_SRCCOLORKEY | SDL_RLEACCEL,
		SDL_MapRGB(image->surf->format, r, g, b));

	return image;
}

bool Graphics::DrawImage(Image* img, int x, int y)
{
	if (Screen == NULL || img->surf == NULL)
		return false;

	SDL_Rect Area;
	Area.x = x;
	Area.y = y;

	SDL_BlitSurface(img->surf, NULL, Screen, &Area);

	return true;
}

bool Graphics::DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY)
{
	if (Screen == NULL || img->surf == NULL)
		return false;

	SDL_Rect Area;
	Area.x = x;
	Area.y = y;

	SDL_Rect SrcArea;
	SrcArea.x = startX;
	SrcArea.y = startY;
	SrcArea.w = endX;
	SrcArea.h = endY;

	SDL_BlitSurface(img->surf, &SrcArea, Screen, &Area);

	return true;
}

void Graphics::WriteText(int x, int y, Uint16 text[100], int sz, int r, int g, int b)
{
	//SDL_Color clr; // Тип для цвета. 4 числа — R, G, B и A, соответственно.
	//clr.r = r;
	//clr.g = g;  // Зададим параметры цвета
	//clr.b = b;
	//TTF_Font * fnt = TTF_OpenFont("courier.ttf", sz); // Загружаем шрифт по заданному адресу размером sz
	//SDL_Rect dest;
	//dest.x = x;
	//dest.y = y;
	//SDL_Surface * TextSurface = TTF_RenderText_Blended(fnt, text, clr); // Переносим на поверхность текст с заданным шрифтом и цветом
	//
	//SDL_BlitSurface(TextSurface, NULL, Screen, &dest);
	////SDL_FreeSurface(TextSurface); // Освобождаем память уже ненужной поверхности
	//TTF_CloseFont(fnt); // Закрываем шрифт

	SDL_Color fontColor = { 255, 0, 0, 255 };
	SDL_Surface *place = 0;
	TTF_Font *font = TTF_OpenFont("courier.ttf", sz);
	SDL_Surface *info = TTF_RenderUNICODE_Solid(font, text, fontColor);

}

void Graphics::Flip()
{
	SDL_Flip(Screen);
	SDL_FillRect(Screen, NULL, 0x000000);
}

