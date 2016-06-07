#include "stdafx.h"
#include "Input.h"

void Input::Update()
{
	while (SDL_PollEvent(&evt));
}

void Input::IndexKeys()
{
	keyDownArray = SDL_GetKeyState(NULL);
	keyTapArray = SDL_GetKeyState(NULL);
}

bool Input::IsKeyboardButtonDown(SDLKey key)
{
	IndexKeys();
	if(keyDownArray[key] == 1)
	{
		return true;
	} 
	false;
}

bool Input::IsKeyboardButtonTap(SDLKey key)
{
	IndexKeys();
	if (keyTapArray[key] == 1)
	{
		keyTapArray[key] = 0;
		return true;
	}
	false;
}

bool Input::IsMouseButtonDown(int key)
{
	if (evt.type == SDL_MOUSEBUTTONDOWN)
		if (evt.button.button == key)
			return true;
	return false;
}

bool Input::IsMouseButtonUp(int key)
{
	if (evt.type == SDL_MOUSEBUTTONUP)
		if (evt.button.button == key)
			return true;
	return false;
}

POINT Input::GetButtonDownCoords()
{
	POINT point;
	point.x = evt.button.x;
	point.y = evt.button.y;

	return point;
}

bool Input::IsKeyDown(int key)
{
	return (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == key);
}

bool Input::IsKeyUp(int key)
{
	return (evt.type == SDL_KEYUP && evt.key.keysym.sym == key);
}

int Input::GetPressedKey()
{
	return evt.key.keysym.sym;
}

bool Input::IsExit()
{
	return (evt.type == SDL_QUIT);
}

