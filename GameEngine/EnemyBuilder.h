#pragma once

#include"Builder.h"

/*
	TODO:
		-> add more aspects in enemy builder
*/

class EnemyBuilder : public Builder
{

	Movement* getMovement() override
	{
		AiMovement* movement = new AiMovement();

		return movement;
	}

public:
	EnemyBuilder()
	{
		aiComponent = true;
	}
};

