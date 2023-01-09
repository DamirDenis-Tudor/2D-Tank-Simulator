#pragma once

#include"Tank.h"
#include"Behavior.h"
#include"AssetsStorage.h"
#include"Vector2i.h"

/*
* Descrierea clasei :
*
*	-> reprezinta sablonul unui creator de obiecte
*
*/
class Builder
{
	friend class Director;

protected:
	string _type ;
	string _color ;

	Component* _result = nullptr;

	virtual ~Builder() { }
	virtual void build() = 0;

	void setAtrributes(string type, string color);
};