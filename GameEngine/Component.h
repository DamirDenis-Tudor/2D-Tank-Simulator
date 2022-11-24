#pragma once

#include"SDL.h"
#include"SDL_image.h"
#include"Vector2i.h"

class Component
{
protected:
	bool _active = true;
public:
	virtual void draw() = 0;
	virtual void update() = 0;

	void enable()
	{
		_active = true;
	}

	void disable()
	{
		_active = false;
	}
};

