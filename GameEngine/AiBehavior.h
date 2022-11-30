#pragma once
#include "Behavior.h"
#include<iostream>

class AiBehavior : public Behavior
{

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override
	{
		_down = true;
		_clicked = true;
		move(position, velocity);
	}

};

