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

	*Nota : desenarea sprite-ul este relativa la camera insa
			 pozitia fizica nu este (trebuie tinut cont de Camera offset)
*/
class Bullet : public Component
{
	friend class Tank;
	friend class SpecialObjectsManager;
private:
	SpriteComponent* _sprite = nullptr;
	Vector2T<int> _position;
	Vector2T<float> _velocity = { 1, 1 };
	float _angle = 0;
	int _damage = 0;
	int _tankId = 0; //specificator pentru posesor
	string _impactAnim;

public:
	Bullet(string type , string impactAnim , int damage,  Vector2T<int> position , float angle , int tankId); 

	~Bullet();

	void update() override;

	void draw() override;
};

