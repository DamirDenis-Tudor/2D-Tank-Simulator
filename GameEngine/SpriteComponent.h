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

	SpriteComponent() {}

	SpriteComponent(const char* source);

	SpriteComponent(SpriteComponent*& sprite);

	~SpriteComponent();

	void setNullPointers()
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

	void isOnCamera();

	void draw() override;

	void update() override;

};


