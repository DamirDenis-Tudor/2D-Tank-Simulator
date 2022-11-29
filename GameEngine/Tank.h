#pragma once

#include"Component.h"
#include"InputBehavior.h"
#include"AiBehavior.h"
#include"Behavior.h"
#include"Bullet.h"
#include"Animation.h"

class Tank : public Component
{
	SpriteComponent* tracks = nullptr;
	SpriteComponent* _body = nullptr;
	SpriteComponent* _cannon = nullptr;

	vector<Component*> _componets;
	vector<Bullet*> _bullets;

	Behavior* _behavior = nullptr;

	Vector2T<int> _position = { 0 , 0 };
	Vector2T<float> _velocity = { 0 , 0 };


public:
	Tank(SpriteComponent* body, SpriteComponent* cannon, Vector2T<int> position, Vector2T<float> velocity , float shotingTime)
		:_body(body), _cannon(cannon), _position(position), _velocity(velocity)

	{
		TimeManager::createTimer(_id, shotingTime);
		_componets.push_back(_body);
		_componets.push_back(_cannon);
	}

	~Tank()
	{
		delete _body;
		delete _cannon;
		delete _behavior;
		_componets.clear();
	}

	void setBehavior(Behavior* behavior)
	{
		_behavior = behavior;
	}

	void draw() override
	{
		for (auto& i : _componets)
		{
			i->draw();
		}

		for (auto& i : _bullets)
		{
			i->draw();
		}

	}

	void update() override
	{
		_behavior->movement(_position, _velocity);
		_behavior->rotationC(_position, _cannon->_angle);
		_behavior->rotationB(_body->_angle);

		syncMovement();

		checkForBullets();

		for (int i = 0; i < size(_componets); i++)
		{
			_componets[i]->update();
			if (!_componets[i]->isActive())
			{
				// make a sitem for animation deletion
				TimeManager::removeTimer(_componets[i]->_id);
				_componets.erase(_componets.begin() + i);
			}
		}

		for (int i = 0; i < size(_bullets); i++)
		{
			_bullets[i]->update();

			if (!_bullets[i]->isActive())
			{
				_componets.push_back(new Animation("BigExplosion", _bullets[i]->_position ));

				delete _bullets[i];
				_bullets.erase(_bullets.begin() + i);
			}
		}
	}

	void syncMovement()
	{
		_body->setPosition(_position - CameraManager::offset);
		_cannon->setPosition(_position - CameraManager::offset);
	}

	void checkForBullets()
	{
		//std::cout << "is lauching : " << _behavior->isLaunchingBullet() << '\n';
		//std::cout << " timer stop: " << !TimeManager::_timers[_id].isTimerWorking() << "\n\n";

 		if (!TimeManager::_timers[_id]->isTimerWorking() && _behavior->isLaunchingBullet())
		{
			TimeManager::_timers[_id]->resetTimer();

			Vector2T<int> circumference =
			{
				static_cast<int>(SDL_cos((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2) ,
				static_cast<int>(SDL_sin((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2)
			};

			_bullets.push_back(new Bullet("Type1", _position + circumference + _cannon->_dest->w / 2, _cannon->_angle));
		}
	}
};

