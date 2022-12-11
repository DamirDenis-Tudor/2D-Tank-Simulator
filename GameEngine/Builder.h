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
	const char* _type = nullptr;
	const char* _color = nullptr;


	Component* _result = nullptr;

	virtual ~Builder() { }
	virtual void build() = 0;

	/*
		atributele de baza pentru orice "produs creat"
	*/
	void setAtrributes(const char* type, const char* color, Vector2T<int> position)
	{
		_type = type;
		_color = color;
		_position = position;
	}
};