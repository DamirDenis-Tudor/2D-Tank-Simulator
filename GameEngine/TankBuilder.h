#pragma once

#include"Builder.h"
#include"Tank.h"
#include"Vector2i.h"
#include"Mediator.h"
#include"CameraManager.h"

class TankBuilder : public Builder
{
	friend class Director;

protected:
	bool playerIdentifier = false;

	Vector2T<int> _position;
	Vector2T<float> _velocity;
	float _shootingTime = 0;
	const char* _type = nullptr;
	const char* _color= nullptr;

	Behavior* _behavior = nullptr;
	void build() override;

public:
	virtual void setBehavior() = 0;
	void setAtrributes(const char* type, const char* color,
		Vector2T<int> position, Vector2T<float> velocity , float shootingTime) override;
};

class AiTank : public TankBuilder
{
public:
	AiTank()
	{
	}

	void setBehavior() override 
	{

		_behavior = nullptr;
		_behavior = new AiBehavior;
	}

};

class PlayerTank : public TankBuilder
{
public:
	PlayerTank()
	{
		playerIdentifier = true;
	}
	void setBehavior() override
	{
		_behavior = nullptr;
		_behavior = new InputBehavior;
	}
};

