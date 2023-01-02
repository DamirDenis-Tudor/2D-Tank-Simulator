#pragma once

#include"Builder.h"
#include"Tank.h"
#include"Vector2i.h"
#include"Mediator.h"
#include"CameraManager.h"


/*
	Descriere:
		-> adauga caracteristici noi specifice unui tank
*/

class TankBuilder : public Builder
{
	friend class Director;

protected:
	bool playerIdentifier = false;
	
	TankAttributes* _attributes = nullptr;
	Behavior* _behavior = nullptr;

	void setTankParameters();
	void build() override;

public:
	virtual void setBehavior() = 0;
};


/*
* Descriere clase:
*	-> specifica explicit comportamentul  
*/


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

