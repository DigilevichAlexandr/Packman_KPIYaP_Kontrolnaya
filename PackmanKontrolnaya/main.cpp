#include "Project.h"

// ������ ����. ������ ��������� � ������� ������ ���� 128x128 ��������
const int GRID_SIZE = 444;


class PacmanScreen : public Screen
{
private:
	Input* input;
	Graphics* graphics;
	Borders* bordersClass;
	Coins* coinsClass;
	
	//����� � ����


	// ����������� ����, ��������� � �������
	Image* back;
	Image* player[2];
	Image* packman;
	Image* ghost_red;
	Image* coinImage;


	// ������� ��� ����������� ������������
	SDL_Rect packman_rect;
	SDL_Rect ghost_red_rect;
	SDL_Rect* borders;
	SDL_Rect* coins;

	// ������, ������������ ����, � ������� �����
	int grid[3][3], currplayer;
	int speed = 1;
	int goOut = 147;
	int yPos, xPos = 0;
	int gameOver = -1;
	struct CurPos { int y, x; } curPos;
	bool goFlag = false;
	bool seekFlag = false;
	bool gotThere = false;
	bool* coinsFlags;

	void StartSettings()
	{
		// ����� ������� Graphics � Input � ������������� ��������� ����

		input = game->GetInput();
		graphics = game->GetGraphics();
		SDL_WM_SetCaption("PackMan", 0);

		borders = bordersClass->MakeBorders();
		coins = coinsClass->MakeCoins();
		coinsFlags = coinsClass->MakeExistingFglags();
	}

	void LoadingImage()
	{
		// �������� �����������

		back = graphics->NewImage("baground.bmp");
		player[0] = graphics->NewImage("2.bmp");
		player[1] = graphics->NewImage("3.bmp");
		packman = graphics->NewImage("pacman.bmp");
		ghost_red = graphics->NewImage("red.bmp");
		coinImage = graphics->NewImage("coin.bmp");
	}

	void Reset()
	{
		// ������� ���� � ����� ����
		goFlag = false;
		gotThere = false;
		curPos.y = 186;
		curPos.x = 210;
		gameOver = -1;

		packman_rect.x = 137;
		packman_rect.y = 273;
		packman_rect.w = packman_rect.h = 22;

		ghost_red_rect.x = 210;
		ghost_red_rect.y = 186;
		ghost_red_rect.w = ghost_red_rect.h = 22;

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				grid[i][j] = 0;

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
		// ��������� ����� ����

		char* message;

		switch (over)
		{
		case 0:
			message = "���� ���� �������, �������. ��� �����?";
			break;
		case 1:
			message = "";
			break;
		case 2:
			message = "";
			break;
			// ���� ���� �� ��������, ������������ �� �������
		default:
			return;
		}

		// ���������� ������������, ����� �� �� ������� ��� ���
		if (MessageBox(0, message, "���� ��������", MB_YESNO) == IDYES)
			Reset();
		else
			game->Exit();
	}

public:
	void Start()
	{
		//MessageBox(0, "������ ������� ���������", "", MB_YESNO);
		StartSettings();
		LoadingImage();
		Reset();
	}

	void Update()
	{
		// ���� ����� ������� ������� � ����
		if (input->IsExit())
			game->Exit();

		// ������ ������
		graphics->DrawImage(back, 0, 0);

		// ������� �������

		if (input->IsKeyboardButtonDown(SDLK_d))
		{
			goFlag = true;
			packman_rect.x += speed;
			for (int i = 0;i < 55;i++)
				if (IsCollisionOccured(&packman_rect, &(borders[i])))
					packman_rect.x -= speed;
		}
		else
			if (input->IsKeyboardButtonDown(SDLK_w))
			{
				goFlag = true;
				packman_rect.y -= speed;
				for (int i = 0;i < 55;i++)
					if (IsCollisionOccured(&packman_rect, &(borders[i])))
						packman_rect.y += speed;
			}
			else
				if (input->IsKeyboardButtonDown(SDLK_a))
				{
					goFlag = true;
					packman_rect.x -= speed;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(&packman_rect, &(borders[i])))
							packman_rect.x += speed;

				}
				else
					if (input->IsKeyboardButtonDown(SDLK_s))
					{
						goFlag = true;
						packman_rect.y += speed;
						for (int i = 0;i < 55;i++)
							if (IsCollisionOccured(&packman_rect, &(borders[i])))
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

		//������ ��� �������, ������� ��� �� � ��������

		for (int i = 0;i < 1;i++)
		{
			if (IsCollisionOccured(&packman_rect, &(coins[i])))
			{
				coinsFlags[i] = false;
			}

			if (coinsFlags[i])
			{
				graphics->DrawImage(coinImage, coins[i].x, coins[i].y);
			}
		}



		//������ �� �������

		//TTF_Font *fntCourier = TTF_OpenFont("courier.ttf",12);

		//SDL_Color clrFg = { 0,0,255,0 };  // Blue ("Fg" is foreground)

		//SDL_Surface *sText = TTF_RenderText_Solid(fntCourier, "Courier 12", clrFg);

		//SDL_Rect rcDest = { 0,0,0,0 };

		//SDL_BlitSurface(sText, NULL, screen, &rcDest);

		//SDL_FreeSurface(sText);


		// ������ �������
		graphics->DrawImage(packman, packman_rect.x, packman_rect.y);

		//������ ���������
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
			borders[54].w = 174;
			yPos = packman_rect.y - ghost_red_rect.y;
			if (yPos != 0)
			{
				if (packman_rect.y > ghost_red_rect.y)
				{
					ghost_red_rect.y++;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(&ghost_red_rect, &(borders[i])))
						{
							ghost_red_rect.y--;
						}
				}
				else
				{
					ghost_red_rect.y--;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(&ghost_red_rect, &(borders[i])))
						{
							ghost_red_rect.y++;
						}
				}
			}
			xPos = packman_rect.x - ghost_red_rect.x;
			if (xPos != 0)
			{
				if (packman_rect.x > ghost_red_rect.x)
				{
					ghost_red_rect.x++;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(&ghost_red_rect, &(borders[i])))
						{
							ghost_red_rect.x--;
						}
				}
				else
				{
					ghost_red_rect.x--;
					for (int i = 0;i < 55;i++)
						if (IsCollisionOccured(&ghost_red_rect, &(borders[i])))
						{
							ghost_red_rect.x++;
						}
				}
			}

		}

		graphics->DrawImage(ghost_red, ghost_red_rect.x, ghost_red_rect.y);

		//������ �����
		//Uint16 tmpch[100] = {'�','�','�','�'};
		/*for (int i = 0; i < 100; i++)
			tmpch[i] = 0;
		sprintf_s(tmpch, "You win!");*/
		//graphics->WriteText(10, 18, tmpch, 20, 0, 255, 0);



		// ������� �� �����
		graphics->Flip();


		/*TTF_CloseFont( fntCourier );*/
		// ������������ ����� ����
		if (IsCollisionOccured(&ghost_red_rect, &packman_rect))
		{
			gameOver = 0;
		}

		GameOverHandle(gameOver);
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	return game.Execute(new PacmanScreen(), GRID_SIZE, GRID_SIZE);
}