#pragma once

#include"SDL.h"
#include"Vector2i.h"

/*
	Descriere clasa:
		-> 
*/

class InputManager
{
private:
	static bool* _keys; // toate codurile pentru taste

public:
	static bool _escape;
	static bool _up;
	static bool _down;
	static bool _left;
	static bool _right;

	static bool clicked;
	static Vector2T<int> mousePos;

private:
	InputManager() {}

public:
	static void clear()
	{
		delete _keys;
		_keys = nullptr;
	}

	static void initInput()
	{
		for (int i = 0; i < 256; i++)
		{
			_keys[i] = false;
		}
	}

	static void update()
	{
		_escape = _keys[SDLK_ESCAPE];
		_up = _keys[SDLK_w];
		_down = _keys[SDLK_s];
		_left = _keys[SDLK_a];
		_right = _keys[SDLK_d];

		SDL_GetMouseState(&mousePos._x, &mousePos._y);
	}

	~InputManager()
	{

	}

	static void keyPressed(SDL_Event event)
	{
		if (event.key.keysym.sym < 256)
		{
			_keys[event.key.keysym.sym] = true;
		}
	}

	static void keyReleased(SDL_Event event)
	{
		if (event.key.keysym.sym < 256)
		{
			_keys[event.key.keysym.sym] = false;
		}
	}


};