#pragma once
#include "Behavior.h"
#include<iostream>

class AiBehavior : public Behavior
{

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override
	{
		_down = true;
		move(position, velocity);
	}


	void rotationC(Vector2T<int>& position, float& angle)
	{
		double posY = static_cast<double>(_target._y)
			- static_cast<double>(position._y) - static_cast<double>(AssetsStorage::_rotCenter->y);

		double posX = static_cast<double>(_target._x) 
			- static_cast<double>(position._x) - static_cast<double>(AssetsStorage::_rotCenter->x);

		angle = (SDL_atan2(posY, posX) * 180 / M_PI) + 90;
	}
};

