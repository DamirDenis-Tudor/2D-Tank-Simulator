#pragma once

#include"Body.h"
#include"Cannon.h"
#include"Component.h"
#include"InputMovement.h"
#include"AiMovement.h"
#include"Movement.h"

class Tank : public Component
{
	SpriteComponent* _body = nullptr;
	SpriteComponent* _cannon = nullptr;
	Movement* _movement = nullptr;

	Vector2T<int> _position = { 0 , 0 };
	Vector2T<float> _velocity = { 0 , 0 };


public:
	Tank(SpriteComponent* body, SpriteComponent* cannon , Vector2T<int> position , Vector2T<float> velocity)
		:_body(body), _cannon(cannon), _position(position) , _velocity(velocity) {}

	~Tank()
	{
		delete _body;
		delete _cannon;
		delete _movement;
	}

	void setMovement(Movement* movement)
	{
		_movement = movement;
	}

	void draw() override
	{
		_body->draw();
		_cannon->draw();
	}

	void update() override
	{
		_movement->move(_position , _velocity);
		syncMovement();
		
		_movement->rotationC(_position ,_cannon->_angle);
		_movement->rotationB(_body->_angle);

		_body->update();
		_cannon->update();

	}

	void syncMovement()
	{
		_body->setPosition(_position - CameraManager::offset  );
		_cannon->setPosition(_position - CameraManager::offset  );
	}
};

