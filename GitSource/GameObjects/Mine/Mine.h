#pragma once

#include"AnimationsHandler.h"
#include"TimeManager.h"
#include"ColisionManager.h"
#include"InfoManager.h"


/*
* Descrierea clasei:
*		-> descriere comportamentul unui mine
*		-> este un obiect Special => inregistare in SpecialObjectManager
*/
class Mine : public Component
{
	friend class SpecialObjectsManager;
private:
	Vector2T<int> _position;
	AnimationComponent* _idle = nullptr; 

	int _tankId = 0; //indetificator pentru posesor
	string _type; //

public:
	Mine(string type , Vector2T<int> position , int tankId);
	~Mine();

	void draw() override;
	void update() override;
};

