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
*	Nota : este clasa abstracta => EnemyBuilder , PlayerBuilder
*
*/

class Builder
{
	friend class Director;

protected:
	const char* _color = nullptr;
	const char* _type = nullptr;

public:

	Builder() {}
	~Builder()
	{
		_color = nullptr;
		_type = nullptr;
	}

	void setAtributtes(const char* color, const char* type)
	{
		_color = color;
		_type = type;
	}
	SpriteComponent* getBody()
	{
		SpriteComponent* body = new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "body"}]);

		return body;
	}

	SpriteComponent* getCannon()
	{
		SpriteComponent* cannon = new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "cannon"}]);

		return cannon;
	}

	SpriteComponent* getTracks()
	{
		SpriteComponent* tracks = new SpriteComponent(AssetsStorage::_movebles[{"tracks"}]);

		return tracks;
	}

	virtual Behavior* getBehavior() = 0;
};

