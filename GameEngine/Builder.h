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
*/
class Builder
{
	friend class Director;

protected:
	Vector2T<int> _position;
	string _type ;
	string _color ;


	Component* _result = nullptr;

	virtual ~Builder() { }
	virtual void build() = 0;

	/*
		atributele de baza pentru orice "produs creat"
	*/
	void setAtrributes(string type, string color, Vector2T<int> position = {0,0})
	{
		_type = type;
		_color = color;
		_position = position;
	}
};