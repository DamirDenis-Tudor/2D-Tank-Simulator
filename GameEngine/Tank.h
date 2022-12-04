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
	vector<Bullet*> _bullets;

	Behavior* _behavior = nullptr;

	Vector2T<int> _position = { 0 , 0 };
	Vector2T<float> _velocity = { 0 , 0 };

	const char* bulletType;

public:
	Tank(SpriteComponent* tracks , SpriteComponent* body, SpriteComponent* cannon , Behavior * behavior, Vector2T<int> position, Vector2T<float> velocity , float shotingTime , const char* type)
		:_tracks(tracks), _body(body), _cannon(cannon), _position(position), _behavior(behavior) , _velocity(velocity), bulletType(type)
	{
		TimeManager::createTimer(_id, shotingTime);

		Mediator::notifyTanksPosition(_position, _id);

		// behaviorul va fi particular tank-ului
		_behavior->setId(_id);
	}

	~Tank()
	{

		_tracks->setNullPointers();
		delete _tracks; _tracks = nullptr;
		
		_body->setNullPointers();
		delete _body; _body = nullptr;

		_cannon->setNullPointers();
		delete _cannon; _cannon = nullptr;

		delete _behavior; _behavior = nullptr;

		for (auto& i : _bullets)
		{
			delete i;
			i = nullptr;
		}
		_bullets.clear();

		TimeManager::removeTimer(_id);
	}

	void syncMovement()
	{
		Mediator::notifyTanksPosition(_position, _id);

		_tracks->setPosition(_position - CameraManager::offset);
		_body->setPosition(_position - CameraManager::offset);
		_cannon->setPosition(_position - CameraManager::offset);

		_tracks->update();
		_body->update();
		_cannon->update();
	}

	void checkForBullets()
	{
		// daca timerul nu este in functiune inseamna ca
		// glotul va fi lansat daca este data "comanda"
 		if (!TimeManager::_timers[_id]->isTimerWorking() && _behavior->isLaunchingBullet())
		{
			TimeManager::_timers[_id]->resetTimer();

			Vector2T<int> circumference =
			{
				static_cast<int>(SDL_cos((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2) ,
				static_cast<int>(SDL_sin((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2)
			};

			/*
				circumference -> pozitia de inceput a bulletului va fi
				de pe contului cercului format de rotatia cannonului
				-> are acelasi unghi cu al cannon-ului; 
			*/

			Bullet* bullet = new Bullet(bulletType, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle, _id);
			_bullets.emplace_back(bullet);
			bullet = nullptr;

			Animation* anim = new Animation("Shot1", _position + circumference + _cannon->_dest->w / 2, _cannon->_angle);
			AnimationsHandler::addAnimation(anim);
			anim = nullptr;
		}
	}
	void draw() override
	{
		_tracks->draw();
		_body->draw();
		_cannon->draw();

		for (auto& i : _bullets)
		{
			i->draw();
		}
	}

	void update() override
	{
		_behavior->movement(_position, _velocity);
		_behavior->rotationC(_position, _cannon->_angle);
		_behavior->rotationB(_body->_angle, _tracks->_angle);

		syncMovement();

		checkForBullets();

		for (int i = 0; i < _bullets.size(); i++)
		{
			_bullets[i]->update();

			if (!_bullets[i]->isActive())
			{
				Animation* anim = new Animation("BigExplosion", _bullets[i]->_position, _cannon->_angle);
				AnimationsHandler::addAnimation(anim);
				anim = nullptr;
				
				//Aici fac dealocarea
				delete _bullets[i];
				_bullets[i] = nullptr;
				_bullets.erase(_bullets.begin() + i);
				i--;
			}
		}
	}
};

