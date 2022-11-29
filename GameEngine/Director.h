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

	Tank* getTank(Vector2T<int> position , Vector2T<float> velocity ,float shotingTime)
	{
		Tank* tank = new Tank(_builder->getBody(), _builder->getCannon() , position , velocity , shotingTime);

		tank->setBehavior(_builder->getBehavior());

		return tank;
	}

};

