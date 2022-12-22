#pragma once

#include"Component.h"
#include"InputBehavior.h"
#include"AiBehavior.h"
#include"Behavior.h"
#include"Bullet.h"
#include"Animation.h"
#include"AnimationsHandler.h"
#include"SpecialObjectsManager.h"
#include "Mediator.h"
#include"Mine.h"

class Tank : public Component
{
	int health = 200;

	SpriteComponent* _tracks = nullptr;
	SpriteComponent* _body = nullptr;
	SpriteComponent* _cannon = nullptr;
	Behavior* _behavior = nullptr;

	Vector2T<int> _position = { 0 , 0 };

	const char* _bulletType = nullptr;

	Vector2T<float> _velocity = { 0 , 0 };
	int _bulletDamage = 0;
	float _shotingTime = 0;
	const char* _shotingAnim = nullptr;
	const char* _impactAnim = nullptr;
	const char* _teamColor = nullptr;

public:
	Tank(SpriteComponent* tracks, SpriteComponent* body, SpriteComponent* cannon,
		Behavior* behavior, Vector2T<float> velocity, float shotingTime, int bulletDamage, const char* bulletType, const char* color,
		const char* shotingAnim, const char* impactAnim);

	~Tank();

	/*
		notifica toate componentele ca sunt urmarite de camera
	*/
	void cameraIsFollowing();

	/*
		instiintam componentele de o modificare de pozitie
	*/
	void syncMovement();

	/*
		
	*/

	void launchMine();
	void launchBullet();


	void checkForHits();

	void temporaryDisable();
	void respawn();

	void draw() override;

	void update() override;
};

