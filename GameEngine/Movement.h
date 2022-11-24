#pragma once

#include "Vector2i.h"
#include "ColisionManager.h"
#include "InputManager.h"

class Movement
{
public:
	virtual void move(Vector2T<int>& position, Vector2T<float> velocity) = 0;
	virtual void rotationC(Vector2T<int>& position , float& angle) = 0;
	virtual void rotationB(float& angle) = 0;
};

