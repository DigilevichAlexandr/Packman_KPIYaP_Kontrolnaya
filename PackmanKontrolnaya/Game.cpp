#include "Game.h"
const int FRAMES_PER_SECOND = 100;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

DWORD next_game_tick = GetTickCount();

Game::Game()
{
	run = true;
}

int Game::Execute(Screen* startscreen, int width, int height)
{
	int sleep_time = 0;
	//bool game_is_running = true;

	graphics = new Graphics(width, height);
	input = new Input();
	screen = startscreen;

	screen->SetController(this);
	this->screen->Start();

	while (run)
	{
		input->Update();
		screen->Update();

		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		if (sleep_time >= 0) {
			Sleep(sleep_time);
		}
		else {
			// Shit, we are running behind!
		}
	}

	screen->Destroy();

	delete graphics;
	delete input;
	delete screen;

	SDL_Quit();
	return 0;
}

Graphics* Game::GetGraphics()
{
	return graphics;
}

Input* Game::GetInput()
{
	return input;
}

Screen* Game::GetScreen()
{
	return screen;
}

void Game::SetScreen(Screen* screen)
{
	this->screen->Destroy();
	delete this->screen;
	this->screen = screen;
	this->screen->SetController(this);
	this->screen->Start();
}

void Game::Exit()
{
	run = false;
}