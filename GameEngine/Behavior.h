#pragma once

#include "Vector2i.h"
#include "ColisionManager.h"
#include"TimeManager.h"
#include"Mediator.h"
#include"MapSpaceManager.h"

/*
	Descriere clasa:

		-> clasa abstracta de descrie compotamentul unui tank:
			- rotatiile pentru body & cannon (independente) 
			- miscare (ce trebuie particularizata) 
*/
class Behavior
{
protected:
	int _id = 0; // indentificator pentru a sti posesorul
	const char* _colorTeam = nullptr; // indentificator pentru apartenenta posesorului

	Moves _moves; 

	//mouse-ul sau un tank pentru Ai
	Vector2T<int> _target = { 0 , 0 };

	// in funtie tank-ul urmarit dde camera
	Vector2T<int> _offset = { 0 , 0 };

public:
	virtual void movement(Vector2T<int>& position, Vector2T<float> velocity) = 0;

	void setId(int id)
	{
		_id = id;
	}

	void setColorTeam(const char* color)
	{
		_colorTeam = color;
	}

	bool isLaunchingBullet()
	{
		if (_moves._shoting)
		{
			return true;
		}
		return false;
	}

	bool isLaunchingMine()
	{
		if (_moves._releaseMine)
		{
			return true;
		}
		return false;
	}

	void move(Vector2T<int>& position, Vector2T<float> velocity);

	void rotationB(float& _angle, float& _angle1);

	void rotationC(Vector2T<int>& position, float& angle);

};

