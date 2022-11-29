#pragma once

#include"Tank.h"
#include"Behavior.h"
#include"AssetsStorage.h"
#include"Vector2i.h"

/*
*/

class Builder 
{
	friend class Director;

protected:
	const char* _color = nullptr;
	const char* _type = nullptr;

public:
	bool godComponent = false;
	bool aiComponent = false;

	void setAtributtes(const char* color, const char* type)
	{
		_color = color;
		_type = type;
	}
	SpriteComponent* getBody() 
	{
		SpriteComponent* body = new SpriteComponent( AssetsStorage::_movebles[{_color , _type , "body"}] );

		body->_isGod = godComponent;
		body->_isAi = aiComponent;

		return body;
	}

	SpriteComponent* getCannon()
	{
		SpriteComponent* cannon = new SpriteComponent(AssetsStorage::_movebles[{_color , _type , "cannon"}]);

		cannon->_isGod = godComponent;
		cannon->_isAi = aiComponent;

		return cannon;
	}

	SpriteComponent* getTracks()
	{
		SpriteComponent* tracks = new SpriteComponent(AssetsStorage::_movebles[{" ", _type, "tracks"}]);

		tracks->_isGod = godComponent;
		tracks->_isAi = aiComponent;

		return tracks;
	}

	

	virtual Behavior* getBehavior() = 0;
};

