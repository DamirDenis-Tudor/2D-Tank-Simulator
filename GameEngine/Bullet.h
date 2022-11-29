#pragma once

#include "SpriteComponent.h"
#include"TimeManager.h"
#include"ColisionManager.h"
#include<string>
using namespace std;

class Bullet : public Component
{
private:
	SpriteComponent* _sprite = nullptr;
	Vector2T<int> _position;
	Vector2T<float> _velocity = { 1, 1 };

public:
	Bullet(string type, Vector2T<int> position , float angle ) : _position(position)
	{
		_sprite = new SpriteComponent(AssetsStorage::_movebles[{"Type1", "bullet"}]);
		_sprite->setPosition(position - _sprite->_dest->w / 2);
		_sprite->_angle = angle;

	}
 
	void update() override
	{
		Vector2T<float> potentialPos;
		potentialPos._x = _position._x;
		potentialPos._y = _position._y;

		potentialPos._x += _velocity._x * SDL_cos((_sprite->_angle - 90 ) * M_PI / 180) * TimeManager::getDeltaTime();
		potentialPos._y += _velocity._y * SDL_sin((_sprite->_angle - 90 ) * M_PI / 180) * TimeManager::getDeltaTime();

		if (CollisionManager::pointCollision(potentialPos))
		{
			disable();
		}
		else
		{
			_position._x = static_cast<int>(potentialPos._x);
			_position._y = static_cast<int>(potentialPos._y);
			_sprite->setPosition(_position - CameraManager::offset - _sprite->_dest->w/2);
		}

	}

	void draw() override
	{
		_sprite->draw();
	}
};
