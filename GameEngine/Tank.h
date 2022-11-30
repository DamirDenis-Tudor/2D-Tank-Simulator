#pragma once

#include"Component.h"
#include"InputBehavior.h"
#include"AiBehavior.h"
#include"Behavior.h"
#include"Bullet.h"
#include"Animation.h"

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

	vector<Component*> _animations;
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

		// behaviorul va fi particular tank-ului
		_behavior->setId(_id);
	}

	~Tank()
	{
		delete _body;
		delete _cannon;
		delete _behavior;
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
		for (auto& i : _animations)
		{
			i->draw();
		}
	}

	void update() override
	{
		_behavior->movement(_position, _velocity);
		_behavior->rotationC(_position, _cannon->_angle);
		_behavior->rotationB(_body->_angle , _tracks->_angle);

		Mediator::notifyTanksPosition(_position, _id);

		syncMovement();

		checkForBullets();

		_tracks->update();
		_body->update();
		_cannon->update();

		for (int i = 0; i < size(_bullets); i++)
		{
			_bullets[i]->update();

			if (!_bullets[i]->isActive())
			{
				_animations.push_back(new Animation("BigExplosion", _bullets[i]->_position , _cannon->_angle));

				delete _bullets[i];
				_bullets.erase(_bullets.begin() + i);
			}
		}

		for (int i = 0; i < size(_animations); i++)
		{
			_animations[i]->update();

			if (!_animations[i]->isActive())
			{
				TimeManager::removeTimer(_animations[i]->_id);
				_animations.erase(_animations.begin() + i);
			}
		}
	}

	void syncMovement()
	{
		_tracks->setPosition(_position - CameraManager::offset);
		_body->setPosition(_position - CameraManager::offset);
		_cannon->setPosition(_position - CameraManager::offset);
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
			_bullets.push_back(new Bullet(bulletType, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle));

			_animations.push_back(new Animation("Shot1", _position + circumference + _cannon->_dest->w / 2 , _cannon->_angle));

		}
	}
};

