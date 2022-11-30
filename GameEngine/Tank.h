#pragma once

#include"Component.h"
#include"InputBehavior.h"
#include"AiBehavior.h"
#include"Behavior.h"
#include"Bullet.h"
#include"Animation.h"

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
	Tank(SpriteComponent* tracks , SpriteComponent* body, SpriteComponent* cannon, Vector2T<int> position, Vector2T<float> velocity , float shotingTime , const char* type)
		:_tracks(tracks), _body(body), _cannon(cannon), _position(position), _velocity(velocity), bulletType(type)

	{
		TimeManager::createTimer(_id, shotingTime);
	}

	~Tank()
	{
		delete _body;
		delete _cannon;
		delete _behavior;
	}

	void setBehavior(Behavior* behavior)
	{
		_behavior = behavior;
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
				_animations.push_back(new Animation("Impact1", _bullets[i]->_position , _cannon->_angle));

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
 		if (!TimeManager::_timers[_id]->isTimerWorking() && _behavior->isLaunchingBullet())
		{
			TimeManager::_timers[_id]->resetTimer();

			Vector2T<int> circumference =
			{
				static_cast<int>(SDL_cos((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2) ,
				static_cast<int>(SDL_sin((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2)
			};

			_bullets.push_back(new Bullet(bulletType, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle));
			_animations.push_back(new Animation("Shot1", _position + circumference + _cannon->_dest->w / 2 , _cannon->_angle));

		}
	}
};

