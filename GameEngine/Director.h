#pragma once

#include"TankBuilder.h"

class Director
{
private:
	static Builder* _builder;

public:

	static void setBuilder(Builder* builder);
	static void setBuilderAttributes(const char* type, const char* color, Vector2T<int> position,
		Vector2T<float> velocity = { 0 , 0 }, float shootingTime = 0);
	static Component* getResult();
	static void clear();

};

