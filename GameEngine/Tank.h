#pragma once

#include"Component.h"
#include"InputBehavior.h"
#include"AiBehavior.h"
#include"Behavior.h"
#include"Bullet.h"
#include"Animation.h"
#include"AnimationsHandler.h"
#include "Mediator.h"

/*
	Descrierea clasei:

		-> behavior partiularizat in funtie de tipul tank-ului
		   (Player sau Enemy) vezi clasele Director si builder
*/

class Tank : public Component
{
	SpriteComponent* _tracks = nullptr;
	SpriteComponent* _body = nullptr;
	SpriteComponent* _cannon = nullptr;
	Behavior* _behavior = nullptr;
	vector<Bullet*> _bullets;

	Vector2T<int> _position = { 0 , 0 };
	Vector2T<float> _velocity = { 0 , 0 };

	const char* bulletType;

public:
	Tank(SpriteComponent* tracks, SpriteComponent* body, SpriteComponent* cannon, Behavior* behavior,
		Vector2T<int> position, Vector2T<float> velocity, float shotingTime, const char* type);

	~Tank();

	void syncMovement();

	void checkForBullets();

	void draw() override;

	void update() override;
};

