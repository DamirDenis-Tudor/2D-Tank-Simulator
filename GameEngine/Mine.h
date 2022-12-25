#pragma once

#include"AnimationsHandler.h"
#include"TimeManager.h"
#include"ColisionManager.h"


class Mine : public Component
{
	friend class SpecialObjectsManager;
private:
	Vector2T<int> _position;
	AnimationComponent* _idle = nullptr;
	bool isTriggered = false;
	int _tankId = 0;
	string _type;

public:
	Mine(string type , Vector2T<int> position , int tankId);
	~Mine();

	void draw() override;
	void update() override;
};

