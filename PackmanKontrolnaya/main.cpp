#include "Project.h"

// ������ ����. ������ ��������� � ������� ������ ���� 128x128 ��������
const int GRID_SIZE = 444;


class PacmanScreen : public Screen
{
private:
	Input* input;
	Graphics* graphics;
	Borders* bordersClass;

	//����� � ����


	// ����������� ����, ��������� � �������
	Image* back;
	Image* player[2];
	Image* packman;
	Image* ghost_red;


	// ������� ��� ����������� ������������
	SDL_Rect packman_rect;
	SDL_Rect* borders;


	// ������, ������������ ����, � ������� �����
	int grid[3][3], currplayer;
	int speed = 1;

	void StartSettings()
	{
		// ����� ������� Graphics � Input � ������������� ��������� ����

		input = game->GetInput();
		graphics = game->GetGraphics();
		SDL_WM_SetCaption("PackMan", 0);

		borders = bordersClass->MakeBorders();
	}

	void LoadingImage()
	{
		// �������� �����������

		back = graphics->NewImage("baground.bmp");
		player[0] = graphics->NewImage("2.bmp");
		player[1] = graphics->NewImage("3.bmp");
		packman = graphics->NewImage("pacman.bmp");
		ghost_red = graphics->NewImage("red.bmp");
	}

	void Reset()
	{
		// ������� ���� � ����� ����

		currplayer = 1;
		packman_rect.x = 137;
		packman_rect.y = 273;
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
		// ��������� ����� ����

		char* message;

		switch (over)
		{
		case 0:
			message = "�����! ������� ������� ��� ���?";
			break;
		case 1:
			message = "�������� ��������! ������� ������� ��� ���?";
			break;
		case 2:
			message = "������ ��������! ������� ������� ��� ���?";
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
			packman_rect.x += speed;
			for (int i = 0;i < 54;i++)
				if (IsCollisionOccured(&packman_rect, &(borders[i])))
					packman_rect.x -= speed;
		}
		else
			if (input->IsKeyboardButtonDown(SDLK_w))
			{
				packman_rect.y -= speed;
				for (int i = 0;i < 54;i++)
					if (IsCollisionOccured(&packman_rect, &(borders[i])))
						packman_rect.y += speed;
			}
			else
				if (input->IsKeyboardButtonDown(SDLK_a))
				{
					packman_rect.x -= speed;
					for (int i = 0;i < 54;i++)
						if (IsCollisionOccured(&packman_rect, &(borders[i])))
							packman_rect.x += speed;

				}
				else
					if (input->IsKeyboardButtonDown(SDLK_s))
					{
						packman_rect.y += speed;
						for (int i = 0;i < 54;i++)
							if (IsCollisionOccured(&packman_rect, &(borders[i])))
								packman_rect.y -= speed;
					}

		//TTF_Font *fntCourier = TTF_OpenFont("courier.ttf",12);

		//SDL_Color clrFg = { 0,0,255,0 };  // Blue ("Fg" is foreground)

		//SDL_Surface *sText = TTF_RenderText_Solid(fntCourier, "Courier 12", clrFg);

		//SDL_Rect rcDest = { 0,0,0,0 };

		//SDL_BlitSurface(sText, NULL, screen, &rcDest);

		//SDL_FreeSurface(sText);



		// ������ �������
		graphics->DrawImage(packman, packman_rect.x, packman_rect.y);

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
		GameOverHandle(GameOver());
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	return game.Execute(new PacmanScreen(), GRID_SIZE, GRID_SIZE);
}