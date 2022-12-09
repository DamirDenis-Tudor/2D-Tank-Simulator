#pragma once

#include"Tank.h"
#include"Behavior.h"
#include"AssetsStorage.h"
#include"Vector2i.h"

/*
* Descrierea clasei :
*
*	-> are rolul de a crea componentele necesare
*	   pentru obiectul cerut de Director;
*
*	Nota : este clasa abstracta => TankBuilder , MenuBuilder
*
*/

class Builder
{
	friend class Director;

protected:
	Vector2T<int> _position;
	const char* _type = nullptr;
	const char* _color = nullptr;

	Component* _result = nullptr;

	virtual ~Builder() { }
	virtual void build() = 0;

	// parametrii de interes sunt cei fara argumente predefinite
	// Exemplu: 
	// ->pentru a creea un tank avem nevoie de toti;
	// ->dar pentru a crea butoane de meniu , doar de primii 3
	// TODO:
	//  -> Implementeaza viteze si shootingTime-uri prestabilite ;

	void setAtrributes(const char* type, const char* color, Vector2T<int> position)
	{
		_type = type;
		_color = color;
		_position = position;
	}
};