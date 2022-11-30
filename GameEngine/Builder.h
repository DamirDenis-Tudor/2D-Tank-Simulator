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
	bool _cameraFocus = false;
	bool _isAi = false;

	void setAtributtes(const char* color, const char* type)
	{
		_color = color;
		_type = type;
	}
	SpriteComponent* getBody() 
	{
		SpriteComponent* body = new SpriteComponent( AssetsStorage::_movebles[{_color , _type , "body"}] );

		body->_isOnCameraFocus = _cameraFocus;
		body->_isAi = _isAi;

		return body;
	}

	SpriteComponent* getCannon()
	{
		SpriteComponent* cannon = new SpriteComponent(AssetsStorage::_movebles[{_color , _type , "cannon"}]);

		cannon->_isOnCameraFocus = _cameraFocus;
		cannon->_isAi = _isAi;

		return cannon;
	}

	SpriteComponent* getTracks()
	{
		SpriteComponent* tracks = new SpriteComponent(AssetsStorage::_movebles[{"tracks"}]);

		tracks->_isOnCameraFocus = _cameraFocus;
		tracks->_isAi = _isAi;

		return tracks;
	}

	

	virtual Behavior* getBehavior() = 0;
};

