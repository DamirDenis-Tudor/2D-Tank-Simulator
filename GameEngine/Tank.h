#pragma once

#include"Component.h"
#include"InputBehavior.h"
#include"AiBehavior.h"
#include"Behavior.h"
#include"Bullet.h"
#include"AnimationComponent.h"
#include"AnimationsHandler.h"
#include"SpecialObjectsManager.h"
#include "Mediator.h"
#include"Mine.h"
#include"TextComponent.h"
#include"InfoManager.h"

#define Health 100
#define MaxMinesNumber 3

struct TankAttributes
{
	const char* _shotingAnim = nullptr;
	const char* _impactAnim = nullptr;
	Vector2T<float> _velocity;
	float _shotingTime = 0;
	int _bulletDamage = 0;
};

class Tank : public Component
{
//	TextComponent* _info = nullptr;
	map<string, SpriteComponent*> _parts;
	TankAttributes* _attributes = nullptr;

	Behavior* _behavior = nullptr;

	Vector2T<int> _position = { 0 , 0 };
	string _type ;
	string _teamColor;

	//timers
	string _launchBulletTimerId;
	string _launchMineTimerId;
	string _restoreLifeTimerId;
	string _respawnTimerId;

public:
	Tank(map<string, SpriteComponent*>& parts, Behavior*& behavior, TankAttributes*& attributes, string type, string color);

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

