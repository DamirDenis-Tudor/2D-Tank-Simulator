#pragma once

#include"Builder.h"

/*
	TODO:
		-> add more aspects in enemy builder
*/

class EnemyBuilder : public Builder
{

	Behavior* getBehavior() override
	{
		AiBehavior* movement = new AiBehavior();

		return movement;
	}

public:
	EnemyBuilder()
	{
		aiComponent = true;
	}
};

