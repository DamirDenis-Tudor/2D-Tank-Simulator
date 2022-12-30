#pragma once

#include "SpriteComponent.h"
#include"TimeManager.h"
#include"ColisionManager.h"
#include<string>
#include"Mediator.h"
#include"InfoManager.h"

using namespace std;

/*
* Descrierea clasei:
*	-> descreire comportamentul unui bullet
*	-> acesta este un obiect special => inregistare in SpecialObjectManager
*/
class Bullet : public Component
{
	friend class Tank;
	friend class SpecialObjectsManager;
private:
	SpriteComponent* _sprite = nullptr;
	Vector2T<int> _position;
	Vector2T<float> _velocity = { 1.2, 1.2 }; // viteza este defoult pentru toate gloantele
	float _angle = 0;
	int _damage = 0;
	int _tankId = 0; //specificator pentru posesor
	string _impactAnim; // animatia de impact este specifica fiecarui bulet

public:
	Bullet(string type , string impactAnim , int damage,  Vector2T<int> position , float angle , int tankId); 

	~Bullet();

	void update() override;

	void draw() override;
};

