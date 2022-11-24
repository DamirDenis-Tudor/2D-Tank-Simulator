#pragma once

#include"Builder.h"
#include"Tank.h"

class Director
{
private:
	Builder* _builder = nullptr;

public:

	void setBuilder(Builder* builder)
	{
		_builder = builder;
	}

	Tank* getTank(Vector2T<int> position , Vector2T<float> velocity)
	{
		Tank* tank = new Tank(_builder->getBody(), _builder->getCannon() , position , velocity);

		tank->setMovement(_builder->getMovement());

		return tank;
	}

};

