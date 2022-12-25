#pragma once

#include"Component.h"
#include"AnimationComponent.h"
#include"TimeManager.h"

/*
	Descriere clasa:
		-> animatiile vor fi prezentate pe ecran in "ultima instanta";
		-> are un vector static de animatii ce este acutualizat de oriunde
		-> poate fi instatiaata, dar cu conditia sa fie ultima componenta instatiata;
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

