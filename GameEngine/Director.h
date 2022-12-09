#pragma once

#include"TankBuilder.h"

class Director
{
private:
	static Builder* _builder;

public:

	static void setBuilder(Builder* builder);
	static void setBuilderAttributes(const char* type, const char* color, Vector2T<int> position);
	static Component* getResult();
	static void clear();

};

