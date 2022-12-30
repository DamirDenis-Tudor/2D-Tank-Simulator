#pragma once

#include"TankBuilder.h"

/*
	Descriere clasa:
		-> primeste un builder
		-> ii comunica niste intructiuni de baza
		-> afera clientului componenta creata de builder
*/
class Director
{
private:
	static Builder* _builder;

public:

	static void setBuilder(Builder* builder);
	static void setBuilderAttributes(string type, string color);
	static Component* getResult();
	static void clear();

};

