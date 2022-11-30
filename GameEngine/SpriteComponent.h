#pragma once

#include"Component.h"
#include"SDL.h"
#include<iostream>

#include "RendererManager.h"
#include "CameraManager.h"

class SpriteComponent : public Component
{
	friend class AssetsStorage;
	friend class Map;
	friend class Tank;
	friend class Bullet;
	friend class Animation;

private:

	SDL_Rect* _src = nullptr;
	SDL_Rect* _dest = nullptr;
	SDL_Texture* _texture = nullptr;
	SDL_Point center = { 64 , 74 };
	float _angle = 0;

public:
	bool _isGod = false;
	bool _isAi = false;
	SpriteComponent(const char* source)
	{
		_src = new SDL_Rect;
		_dest = new SDL_Rect;
		SDL_Surface* surface = IMG_Load(source);
		_texture = SDL_CreateTextureFromSurface(RendererManager::getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	SpriteComponent() {}

	SpriteComponent(SpriteComponent*& sprite)
	{

		_src = new SDL_Rect;
		*_src = *sprite->_dest;

		_dest = new SDL_Rect;
		*_dest = *sprite->_dest;

		_texture = sprite->_texture;
	}

	~SpriteComponent()
	{

	}

	void setAngle(float angle)
	{
		_angle = angle;
	}

	void setPosition(Vector2T<int> position)
	{
		_dest->x = position.getX();
		_dest->y = position.getY();
	}

	void draw() override
	{
		if (_active)
		{
			SDL_RenderCopyEx(RendererManager::_renderer, _texture, _src, _dest ,_angle , &center , SDL_FLIP_NONE);
		//	SDL_RenderDrawRect(RendererManager::_renderer, _dest);
		}
	}

	void update() override
	{
		if (!_isGod )
		{
			isOnCamera();

			if (_isAi)
			{
				_dest->x = _dest->x + CameraManager::tileOffset._x;
				_dest->y = _dest->y + CameraManager::tileOffset._y;
			}
			else
			{
				_dest->x = _dest->x - CameraManager::tileOffset._x;
				_dest->y = _dest->y - CameraManager::tileOffset._y;
			}
		}
	}
	void isOnCamera()
	{
		if (_dest->x + _dest->w  < -64 ||
			_dest->y + _dest->h  < -64 ||
			_dest->x  > RendererManager::_width  + 64 ||
			_dest->y  > RendererManager::_heigth + 64)
		{
			disable();
		}
		enable();
	}
};


