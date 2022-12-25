#pragma once

#include"Component.h"
#include"SDL.h"
#include<iostream>

#include "RendererManager.h"
#include "CameraManager.h"


/*
	Descriere classei:
		-> constructori cu parametri:
			- folosit la incarcarea in memorie a sprite-urilor
			   (folosit doar in AssetsStorage)
		-> contructor de copiere (se aloca memorie dor pentru _dest) :
			- folosit la crearea mapei (fac o copie din memorie a sprite-ului)
			- sau la Animatii si posibil si in alte locuri
		-> se deseneaza sprite-ul doar daca este in cadrul camerei
		-> indetificator pentru obiectul urmarit de camera (default este player-ul)
*/
class SpriteComponent : public Component
{
	friend class AssetsStorage;
	friend class Map;
	friend class MiniMap;
	friend class Tank;
	friend class Bullet;
	friend class AnimationComponent;

protected:
	SDL_Rect* _src = nullptr;
	SDL_Rect* _dest = nullptr;
	SDL_Texture* _texture = nullptr;
	SDL_Point center = { 64 , 74 };
	float _angle = 0;

	bool _isTemporaryDeactivated = false; 
	bool _isFollowed = false;
	bool _isTile = false;
	bool _isMiniTile = false;
public:
	SpriteComponent() {}

	SpriteComponent(const char* source , int sourceDim = 0 , int destDim = 0 );

	SpriteComponent(SpriteComponent*& sprite);

	~SpriteComponent();

	/*
		-> functie apelata pentru stergerea unor copii de sprite-uri
	*/
	void setSrcTextNullPtr() 
	{
		_src = nullptr;
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

	Vector2T<int> getPosition()
	{
		return Vector2T<int>(_dest->x, _dest->y);
	}

	void setScaleDimension(int width , int height)
	{
		_dest->w = width;
		_dest->h = height;
	}

	void setOpacity(int opacity)
	{
		SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_texture, opacity);
	}

	void isOnCamera();

	void draw() override;

	void update() override;

};


