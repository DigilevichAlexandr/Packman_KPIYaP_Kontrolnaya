#include "Project.h"

// Размер поля. Размер крестиков и ноликов должен быть 128x128 пикселей
const int GRID_SIZE = 444;
const int POINTS_NUM = 4;

class PacmanScreen : public Screen
{
private:
	Input* input;
	Graphics* graphics;
	Borders* bordersClass;
	Coins* coinsClass;
	SeekPoints*  seekPointsClass;

	//текст в углу


	// Изображения фона, крестиков и ноликов
	Image* back;
	Image* player[2];
	Image* packman;
	Image* ghost_red;
	Image* ghost_green;
	Image* ghost_blue;
	Image* coinImage;
	Image* door;

	// Области для определения столкновения
	SDL_Rect packman_rect;
	SDL_Rect ghost_red_rect;
	SDL_Rect ghost_green_rect;
	SDL_Rect ghost_blue_rect;
	SDL_Rect* borders;
	SDL_Rect* coins;
	SDL_Rect door_rect_left, door_rect_right;
	SDL_Rect* seekPoints;

	// Массив, обозначающий поле, и текущий игрок
	int grid[3][3], currplayer;
	int speed = 1;
	int goOut = 147;
	int yPos, xPos = 0;
	int gameOver = -1;
	int score;
	int coin_count = 0;
	int move_green_x = 0;
	int move_green_y = 0;
	int move_blue_x = 0;
	int move_blue_y = 0;
	int targetNum = 0;
	struct CurPos { int y, x; } curPos;
	bool goFlag = false;
	bool seekFlag = false;
	bool gotThere = false;
	bool* coinsFlags;
	bool is_open_door = false;
	bool lvl = 1;
	bool seek = false;

	void StartSettings()
	{
		// Берем объекты Graphics и Input и устанавливаем заголовок окна

		input = game->GetInput();
		graphics = game->GetGraphics();
		SDL_WM_SetCaption("PackMan", 0);

		borders = bordersClass->MakeBorders();
		coins = coinsClass->MakeCoins();
		//coinsFlags = coinsClass->MakeExistingFglags();
	}

	void LoadingImage()
	{
		// Загрузка изображений

		back = graphics->NewImage("baground.bmp");
		packman = graphics->NewImage("pacman.bmp");
		ghost_red = graphics->NewImage("red.bmp");
		ghost_green = graphics->NewImage("green.bmp");
		ghost_blue = graphics->NewImage("blue.bmp");
		coinImage = graphics->NewImage("coin.bmp");
		door = graphics->NewImage("door.bmp");
	}

	void Reset()
	{
		// Очистка поля и вывод фона
		score = 0;
		goFlag = false;
		gotThere = false;
		is_open_door = false;
		curPos.y = 186;
		curPos.x = 210;
		gameOver = -1;
		coin_count = 0;
		lvl = 1;
		seek = false;
		seekPoints = seekPointsClass->MakeSeekPoints();

		packman_rect.x = 380;
		packman_rect.y = 190;
		packman_rect.w = packman_rect.h = 22;

		ghost_red_rect.x = 210;
		ghost_red_rect.y = 186;
		ghost_red_rect.w = ghost_red_rect.h = 22;

		ghost_green_rect.x = 172;
		ghost_green_rect.y = 186;
		ghost_green_rect.w = ghost_green_rect.h = 22;

		ghost_blue_rect.x = 249;
		ghost_blue_rect.y = 186;
		ghost_blue_rect.w = ghost_blue_rect.h = 22;

		door_rect_left.x = 2;
		door_rect_right.y = door_rect_left.y = 188;
		door_rect_right.w = door_rect_left.w = 5;
		door_rect_right.h = door_rect_left.h = 29;

		door_rect_right.x = 436;

		coinsFlags = coinsClass->MakeExistingFglags();

		/*graphics->DrawImage(back, 0, 0);
		graphics->DrawImage(packman, packman_rect.x, packman_rect.y + 11);*/
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
			message = "Надо быть шустрее, дружище. Еще разок?";
			break;
			////case 1:
			////	message = "Уровень" + itoa(lvl);
			////	break;
		case 2:
			message = "";
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
			goFlag = true;
			packman_rect.x += speed;
			for (int i = 0;i < 55;i++)
				if (IsCollisionOccured(&packman_rect, &(borders[i])) || ((IsCollisionOccured(&packman_rect, &door_rect_left) || IsCollisionOccured(&packman_rect, &door_rect_right)) && !is_open_door))
					packman_rect.x -= speed;
		}
		else
			if (input->IsKeyboardButtonDown(SDLK_w))
			{
				goFlag = true;
				packman_rect.y -= speed;
				for (int i = 0;i < 55;i++)
					if (IsCollisionOccured(&packman_rect, &(borders[i])) || ((IsCollisionOccured(&packman_rect, &door_rect_left) || IsCollisionOccured(&packman_rect, &door_rect_right)) && !is_open_door))
						packman_rect.y += speed;
			}
			else
				if (input->IsKeyboardButtonDown(SDLK_a))
				{
					goFlag = true;
					packman_rect.x -= speed;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(&packman_rect, &(borders[i])) || ((IsCollisionOccured(&packman_rect, &door_rect_left) || IsCollisionOccured(&packman_rect, &door_rect_right)) && !is_open_door))
							packman_rect.x += speed;
				}
				else
					if (input->IsKeyboardButtonDown(SDLK_s))
					{
						goFlag = true;
						packman_rect.y += speed;
						for (int i = 0;i < 55;i++)
							if (IsCollisionOccured(&packman_rect, &(borders[i])) || ((IsCollisionOccured(&packman_rect, &door_rect_left) || IsCollisionOccured(&packman_rect, &door_rect_right)) && !is_open_door))
								packman_rect.y -= speed;
					}
					else
					{
						if (input->IsKeyboardButtonDown(SDLK_r))
						{
							Reset();
							return;
						}
						/*else
						{
							if (input->IsKeyboardButtonTap(SDLK_f))
							{

							}
						}*/
					}

		//Пакман ест монетки, которые тут же и рисуются

		coin_count = 0;
		for (int i = 0;i < 11;i++)
		{
			if (IsCollisionOccured(&packman_rect, &(coins[i])))
			{
				coinsFlags[i] = false;
				score++;
			}

			if (coinsFlags[i])
			{
				graphics->DrawImage(coinImage, coins[i].x, coins[i].y);
			}
			else
			{
				coin_count++;
			}
		}

		if (coin_count >= lvl)
		{
			is_open_door = true;
		}

		//работа со шрифтом

		//TTF_Font *fntCourier = TTF_OpenFont("courier.ttf",12);

		//SDL_Color clrFg = { 0,0,255,0 };  // Blue ("Fg" is foreground)

		//SDL_Surface *sText = TTF_RenderText_Solid(fntCourier, "Courier 12", clrFg);

		//SDL_Rect rcDest = { 0,0,0,0 };

		//SDL_BlitSurface(sText, NULL, screen, &rcDest);

		//SDL_FreeSurface(sText);


		// Рисуем двери

		if (!is_open_door)
		{
			graphics->DrawImage(door, door_rect_left.x, door_rect_left.y);
			graphics->DrawImage(door, door_rect_right.x, door_rect_right.y);
		}

		// Рисуем пакмана
		graphics->DrawImage(packman, packman_rect.x, packman_rect.y);

		//Рисуем призраков
		gotThere = curPos.y > goOut;
		if (gotThere)
		{
			if (goFlag)
			{
				ghost_red_rect.y = curPos.y--;
			}
		}
		else
		{
			borders[54].x = 207;
			borders[54].y = 174;
			borders[54].h = 6;
			borders[54].w = 28;
			GhostsSeek(&ghost_red_rect, &packman_rect);
		}

		if (seek)
		{
			GhostsSeek(&ghost_green_rect, &(seekPoints[targetNum]));
			GhostsSeek(&ghost_blue_rect, &(seekPoints[(targetNum + 1) % POINTS_NUM]));
		}
		else
		{
			GhostsGoesOut();
		}

		graphics->DrawImage(ghost_red, ghost_red_rect.x, ghost_red_rect.y);
		graphics->DrawImage(ghost_green, ghost_green_rect.x, ghost_green_rect.y);
		graphics->DrawImage(ghost_blue, ghost_blue_rect.x, ghost_blue_rect.y);

		//рисуем текст
		//Uint16 tmpch[100] = {'п','р','и','в'};
		/*for (int i = 0; i < 100; i++)
			tmpch[i] = 0;
		sprintf_s(tmpch, "You win!");*/
		//graphics->WriteText(10, 18, tmpch, 20, 0, 255, 0);

		// Выводим на экран
		graphics->Flip();

		/*TTF_CloseFont( fntCourier );*/

		// Обрабатываем конец игры (столкновение с призраком)
		if (IsCollisionOccured(&ghost_red_rect, &packman_rect) || IsCollisionOccured(&ghost_blue_rect, &packman_rect) || IsCollisionOccured(&ghost_green_rect, &packman_rect))
		{
			gameOver = 0;
		}

		//обрабатываем переход на новый уровень
		if ((IsCollisionOccured(&packman_rect, &door_rect_left) || IsCollisionOccured(&packman_rect, &door_rect_right)) && is_open_door)
		{
			int temp_lvl = lvl;
			Reset();
			lvl = temp_lvl + 1;
		}

		GameOverHandle(gameOver);
	}

	void GhostsGoesOut()
	{
		if (goFlag)
		{
			if (ghost_green_rect.x < 210)
			{
				ghost_green_rect.x++;
			}
			else
			{
				if (ghost_green_rect.y > 149)
				{
					ghost_green_rect.y--;
					ghost_blue_rect.y--;
				}
				else
				{
					goFlag = false;
					seek = true;
				}
			}

			if (ghost_blue_rect.x > 210)
			{
				ghost_blue_rect.x--;
			}
		}
	}

	void GhostsSeek(SDL_Rect* hunter, SDL_Rect* target)
	{
		if (IsCollisionOccured(hunter, target))
		{
			targetNum = (targetNum + 1) % POINTS_NUM;
		}
		else
		{
			yPos = target->y - hunter->y;
			if (yPos != 0)
			{
				if (target->y > hunter->y)
				{
					hunter->y++;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(hunter, &(borders[i])))
						{
							hunter->y--;
						}
				}
				else
				{
					hunter->y--;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(hunter, &(borders[i])))
						{
							hunter->y++;
						}
				}
			}
			xPos = target->x - hunter->x;
			if (xPos != 0)
			{
				if (target->x > hunter->x)
				{
					hunter->x++;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(hunter, &(borders[i])))
						{
							hunter->x--;
						}
				}
				else
				{
					hunter->x--;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(hunter, &(borders[i])))
						{
							hunter->x++;
						}
				}
			}
		}
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	return game.Execute(new PacmanScreen(), GRID_SIZE, GRID_SIZE);
}

