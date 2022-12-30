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

/*
* Descrierea clasa:
*	-> creaza obiecte speciale : mine , gloante
*	-> este format din partie(Sprtite-uri suprapuse)
*	-> miscarile body-ului/ cannon-ului sunt independete 
*      tank-ul fiind controlat in functie de behavior
*   -> prezita o serie de timere pentru durata diferitelor animatii
*      precum si pentru shooting , respawn si depuenre a minelor
*/
class Tank : public Component
{
	map<string, SpriteComponent*> _parts;
	TankAttributes* _attributes = nullptr;

	Behavior* _behavior = nullptr;

	Vector2T<int> _position = { 0 , 0 };
	string _type ;
	string _teamColor;

	//timers
	string _launchBulletTimerId;
	string _launchMineTimerId;
	string _healingTimerId;
	string _respawnTimerId;

	//varibile pentru abilitati
	Vector2T<float> _normalVelocity;
	bool _invincible = false;

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

	void launchMine();
	void launchBullet();

	void checkOfHits();
	void checkOfHealing();
	void checkOfAbilities();

	void temporaryDisable();
	void respawn();

	void draw() override;

	void update() override;
};

