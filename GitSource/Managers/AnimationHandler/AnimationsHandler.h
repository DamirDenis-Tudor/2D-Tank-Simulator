#pragma once

#include"Component.h"
#include"AnimationComponent.h"
#include"TimeManager.h"

/*
	Descriere clasa:
		-> colecteaza animatiile din orice moment
		   al jocului si le prezita pe ercran in ultima instanta
*/
class AnimationsHandler : public Component
{
	static vector<AnimationComponent*> _animations; 
public:
	AnimationsHandler () {}

	~AnimationsHandler();

	static void addAnimation(AnimationComponent* animation)
	{
		_animations.emplace_back(animation);
	}

	void update() override;

	void draw() override;
};

