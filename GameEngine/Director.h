#pragma once

#include"TankBuilder.h"

/*
	Descriere clasa:
		-> primeste un builder
		-> ii comunica niste intructiuni de baza
		-> returneaza componenta creata de builder
*/
class Director
{
private:
	static Builder* _builder;

public:

	static void setBuilder(Builder* builder);
	static void setBuilderAttributes(const char* type, const char* color, Vector2T<int> position = {0,0});
	static Component* getResult();
	static void clear();

};

