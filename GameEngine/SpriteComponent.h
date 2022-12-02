#pragma once

#include"Component.h"
#include"SDL.h"
#include<iostream>

#include "RendererManager.h"
#include "CameraManager.h"

/*
	Descriere clasa:

		-> constructori cu parametri:
			- folosit la incarcarea in memorie a sprite-urilor
			   (folosit doar in AssetsStorage)
		
		-> contructor de copiere : 
			- folosit la crearea mapei (fac o copie din memorie a sprite-ului)
			- sau la Animatii si posibil si in alte locuri
			- sunt smecher
			
			!!!Nota : ALOC MEMORIE DOAR PENTRU _DEST PENTRU CA ESTE NECESAR,
					  IAR PENTRU TEXTURA, _SRC "DOAR" POINTEZ CATRE LOCATIA DIN AssetsStorage

		-> desenez sprite-ul doar daca este in cadrul camerei

		->indetificator pentru obiectul urmarit de camera (default este player-ul)
			- ma mai gandesc daca o sa dau posibiliatea de a centra camera pe ce obiect vreau
			- iuhu!			
*/

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
	bool _isOnCameraFocus = false;
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
		_src = sprite->_src;

		_dest = new SDL_Rect;
		*_dest = *sprite->_dest;

		_texture = sprite->_texture;
	}

	~SpriteComponent()
	{
	
		
	}
	void clear() override
	{
		//ATENTIE : in cazul instantierilor create prin
		// constructorul de copiere
		// doar pentru _dest am alocat
		// memorie => pentru src si texture setam nullptr

		//	Nota : pentru dealocarea _src si _texture se va utiliza suplimetar
		//  in constructorul din clasa AssetsStorage functia de finalClear

		// Exemplu : daca avem un bullet si este distrus nu vream sa
		// dealocam _textura si _src, deoarec pentru urmatorul bullet
		// poiterii _src si _texture voi pointa catre NULL

		_src = nullptr;
		free( _dest);
		_dest = nullptr;
		_texture = nullptr;
		center = { 0 , 0 };
		_angle = 0;
		_id = 0;
	}

	void finalClear()
	{
		//In Assets manager metoda va fi apelata inainte de delete!!
		delete _src;
		_src = nullptr;
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
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
		if (isActive())
		{
			SDL_RenderCopyEx(RendererManager::_renderer, _texture, _src, _dest ,_angle , &center , SDL_FLIP_NONE);
			//SDL_RenderDrawRect(RendererManager::_renderer, _dest);
		}
	}

	void update() override
	{
		if (!_isOnCameraFocus )
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


