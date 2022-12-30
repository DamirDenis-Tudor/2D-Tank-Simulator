#pragma once

#include"Component.h"
#include"SDL.h"
#include<iostream>

#include "RendererManager.h"
#include "CameraManager.h"


/*
	Descriere classei:
		-> reprezinta entitate de baza pentru 
		   un obiect desenabil pe ecran
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
	static SDL_Point center;
	float _angle = 0;

	bool _isFollowed = false; // poate sau nu sa fie urmarit de camera
	bool _isMapObject = false; // 
	bool _isMiniTile = false; //
	bool _isSpawnble = false; // poate un obiect de pe mapa spawnabil
	bool _isObjectDrawble = true; // 
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

	void setCameraPosition(Vector2T<int> position)
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


