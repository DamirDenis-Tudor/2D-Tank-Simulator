#pragma once

#include"Builder.h"

class EnemyBuilder : public Builder
{

	Behavior* getBehavior() override
	{
		AiBehavior* movement = new AiBehavior();

		return movement;
	}

public:
};

