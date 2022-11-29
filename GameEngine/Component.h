#pragma once

#include"SDL.h"
#include"SDL_image.h"
#include"Vector2i.h"
#include<list>
#include<map>
#include<vector>

using namespace std;

class Component
{
protected:
	bool _active = true;

	static int _counter;
	int _id;
public:

	Component()
	{
		_id = _counter;
		_counter++;
	}

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

	bool isActive()
	{
		return _active;
	}

};

