#pragma once

#include"Component.h"
#include"Animation.h"
#include"TimeManager.h"

class AnimationsHandler : public Component
{
	static vector<Animation*> _animations;
public:
	AnimationsHandler () {}

	~AnimationsHandler();

	static void addAnimation(Animation* animation)
	{
		_animations.emplace_back(animation);
	}

	void update() override;

	void draw() override;
};

