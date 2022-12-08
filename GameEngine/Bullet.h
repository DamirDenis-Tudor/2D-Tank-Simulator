#pragma once

#include "SpriteComponent.h"
#include"TimeManager.h"
#include"ColisionManager.h"
#include<string>
#include"Mediator.h"

using namespace std;

/*
* Descrierea clasei:
*
	-> pentru coliziunea obiectului de tip bullet se
	   considera punctul de mijloc al acestuia

	Nota* -> desenarea sprite-ul este relativa la camera insa
			 pozitia fizica nu este (trebuie tinut cont de Camera offset)
*/

class Bullet : public Component
{
	friend class Tank;
private:
	SpriteComponent* _sprite = nullptr;
	Vector2T<int> _position;
	Vector2T<float> _velocity = { 1, 1 };
	int _tankId = 0;

public:
	Bullet(string type, Vector2T<int> position, float angle, int tankId); 

	~Bullet();

	void update() override;

	void draw() override;
};

