#pragma once

#include"Builder.h"

class PlayerBuilder : public Builder
{
	Behavior* getBehavior() override
	{
		InputBehavior* behavior = new InputBehavior();

		return behavior;
	}
public:
	PlayerBuilder()
	{
		_cameraFocus = true;
	}

};

