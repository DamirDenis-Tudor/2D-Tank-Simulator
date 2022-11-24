#pragma once

#include"Builder.h"

class PlayerBuilder : public Builder
{
	Movement* getMovement() override
	{
		InputMovement* movement = new InputMovement();

		return movement;
	}
public:
	PlayerBuilder()
	{
		godComponent = true;
	}

};

