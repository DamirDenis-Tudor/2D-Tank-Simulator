#pragma once

#include "Vector2i.h"
#include "ColisionManager.h"
#include"TimeManager.h"
#include"Mediator.h"
#include"MapSpaceManager.h"

/*
	Descriere clasa:

		-> clasa abstracta de descrie compotamentul unui tank:
			> rotatii de doua feluri , miscare 

		Nota: in clasei mostenitoare metoda vIrtuala pura movement permite
			  implementarea unui movemnt particular fara a modifica clasa tank
*/

class Behavior
{
protected:
	int _id = 0;

	Moves _moves;
	bool _isShooting = false;

	//mouse-ul sau un alt tank pentru Ai
	Vector2T<int> _target = { 0 , 0 };

	// daca este PlayerBehavior _offset-ul va fi cel al camerei
	Vector2T<int> _offset = { 0 , 0 };

public:
	virtual void movement(Vector2T<int>& position, Vector2T<float> velocity) = 0;

	void setId(int id)
	{
		_id = id;
	}

	bool isLaunchingBullet()
	{
		if (_isShooting)
		{
			return true;
		}
		return false;
	}

	void move(Vector2T<int>& position, Vector2T<float> velocity);

	void rotationB(float& _angle, float& _angle1);

	void rotationC(Vector2T<int>& position, float& angle);

};

