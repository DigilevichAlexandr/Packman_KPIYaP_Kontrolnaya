#include "Project.h"

// Размер поля. Размер крестиков и ноликов должен быть 128x128 пикселей
const int GRID_SIZE = 444;

class PacmanScreen : public Screen
{
private:
	Input* input;
	Graphics* graphics;
	Borders* bordersClass;

	// Изображения фона, крестиков и ноликов
	Image* back;
	Image* player[2];
	Image* packman;
	Image* ghost_red;

	// Области для определения столкновения
	SDL_Rect packman_rect;
	SDL_Rect* borders;


	// Массив, обозначающий поле, и текущий игрок
	int grid[3][3], currplayer;

	void StartSettings()
	{
		// Берем объекты Graphics и Input и устанавливаем заголовок окна

		input = game->GetInput();
		graphics = game->GetGraphics();
		SDL_WM_SetCaption("PackMan", 0);

		borders = bordersClass->MakeBorders();
	}

	void LoadingImage()
	{
		// Загрузка изображений

		back = graphics->NewImage("baground.bmp");
		player[0] = graphics->NewImage("2.bmp");
		player[1] = graphics->NewImage("3.bmp");
		packman = graphics->NewImage("pacman.bmp");
		ghost_red = graphics->NewImage("red.bmp");
	}

	void Reset()
	{
		// Очистка поля и вывод фона

		currplayer = 1;
		packman_rect.x = 14;
		packman_rect.y = 67;
		packman_rect.w = packman_rect.h = 22;

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				grid[i][j] = 0;

		graphics->DrawImage(back, 0, 0);
		graphics->DrawImage(packman, packman_rect.x, packman_rect.y + 11);
		graphics->Flip();
	}

	int GameOver()
	{
		return -1;
	}

	bool IsCollisionOccured(SDL_Rect* rect1, SDL_Rect* rect2)
	{
		bool XColl = 0;
		bool YColl = 0;

		if ((rect1->x + rect1->w >= rect2->x) && (rect1->x <= rect2->x + rect2->w)) XColl = 1;
		if ((rect1->y + rect1->h >= rect2->y) && (rect1->y <= rect2->y + rect2->h)) YColl = 1;

		if (XColl&YColl) { return 1; }
		return 0;
	}

	void GameOverHandle(int over)
	{
		// Обработка конца игры

		char* message;

		switch (over)
		{
		case 0:
			message = "Ничья! Желаете сыграть еще раз?";
			break;
		case 1:
			message = "Крестики победили! Желаете сыграть еще раз?";
			break;
		case 2:
			message = "Нолики победили! Желаете сыграть еще раз?";
			break;
			// Если игра не окончена, возвращаемся из функции
		default:
			return;
		}

		// Спрашиваем пользователя, хочет ли он сыграть еще раз
		if (MessageBox(0, message, "Игра окончена", MB_YESNO) == IDYES)
			Reset();
		else
			game->Exit();
	}

public:
	void Start()
	{
		//MessageBox(0, "Выбери уровень сложности", "", MB_YESNO);
		StartSettings();
		LoadingImage();
		Reset();
	}

	void Update()
	{
		// Если нажат красный крестик в окне
		if (input->IsExit())
			game->Exit();

		// Рисуем задник
		graphics->DrawImage(back, 0, 0);

		// Двигаем Пакмана
		if (input->IsKeyboardButtonDown(SDLK_d))
		{
			packman_rect.x++;
			for (int i = 0;i < 52;i++)
				if (IsCollisionOccured(&packman_rect, &(borders[i])))
					packman_rect.x--;
		}
		else
			if (input->IsKeyboardButtonDown(SDLK_w))
			{
				packman_rect.y--;
				for (int i = 0;i < 52;i++)
					if (IsCollisionOccured(&packman_rect, &(borders[i])))
						packman_rect.y++;
			}
			else
				if (input->IsKeyboardButtonDown(SDLK_a))
				{
					packman_rect.x--;
					for (int i = 0;i < 52;i++)
						if (IsCollisionOccured(&packman_rect, &(borders[i])))
							packman_rect.x++;

				}
				else
					if (input->IsKeyboardButtonDown(SDLK_s))
					{
						packman_rect.y++;
						for (int i = 0;i < 52;i++)
							if (IsCollisionOccured(&packman_rect, &(borders[i])))
								packman_rect.y--;
					}



		// Рисуем пакмана
		graphics->DrawImage(packman, packman_rect.x, packman_rect.y);

		// Выводим на экран
		graphics->Flip();

		// Обрабатываем конец игры
		GameOverHandle(GameOver());
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	return game.Execute(new PacmanScreen(), GRID_SIZE, GRID_SIZE);
}