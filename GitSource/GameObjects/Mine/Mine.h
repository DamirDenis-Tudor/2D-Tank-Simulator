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
class Mine : public AnimationComponent
{
private:
	int _tankId = 0; //indetificator pentru posesor
	string _name; //

public:
	Mine(string type , Vector2T<int> position , int tankId);
	~Mine();

	string getType()
	{
		return _name;
	}

	int getTankId()
	{
		return _tankId;
	}

	void update() override;
};

