#pragma once

#include"Builder.h"
#include"Tank.h"

/*
	Descriere clasa:

		-> modalitatea de creare a tank-ului urmareste 
		   design pattern-ul Builder.
		  
		->Directorul primeste un builder care este specializat pe un anumit 
		  tip de tank. Directul nu este interesat ce fel de builder este,
		  el doar "scoate" in productie un tank;

*/

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
		Tank* tank = new Tank(_builder->getTracks(), _builder->getBody(), _builder->getCannon(), position, velocity, shotingTime, _builder->_type);

		tank->setBehavior(_builder->getBehavior());

		return tank;
	}

};

