#ifndef _INPUT_H_
#define _INPUT_H_

#include "Project.h"

class Input
{
private:
	SDL_Event evt;
	Uint8* keyDownArray;
	Uint8* keyTapArray;

public:
	void Update();

	void IndexKeys(); // массив ввода с клавиатуры
	bool Input::IsKeyboardButtonDown(SDLKey key);
	bool Input::IsKeyboardButtonTap(SDLKey key);
	bool IsMouseButtonDown(int key);
	bool IsMouseButtonUp(int key);
	POINT GetButtonDownCoords();

	bool IsKeyDown(int key);
	bool IsKeyUp(int key);
	int GetPressedKey();

	bool IsExit();
};

#endif