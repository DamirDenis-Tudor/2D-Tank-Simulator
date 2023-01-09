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
	friend class Tank;
protected:
	SDL_Rect* _src = nullptr;
	SDL_Rect* _dest = nullptr;
	SDL_Texture* _texture = nullptr;
	static SDL_Point center;
	float _angle = 0;

	bool _isFollowed = false; // poate sau nu sa fie urmarit de camera
	bool _isMapObject = false; // 
	bool _hasBorder = false; //
	bool _isSpawnble = false; // poate un obiect de pe mapa spawnabil
	bool _isObjectDrawble = true; // 
public:
	SpriteComponent() {}

	SpriteComponent(const char* source , int sourceWidth = 0  ,int sourceHeight = 0  , int destWidth = 0 , int destHeight = 0 );

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

	/*
	* seters
	*/

	/*
	* seteaza unghiul de desenare
	*/
	void setAngle(float angle)
	{
		_angle = angle;
	}

	/*
	* seteaza pozitia relativa la camera
	*/
	void setCameraPosition(Vector2T<int> position)
	{
		_dest->x = position.getX();
		_dest->y = position.getY();
	}

	/*
	* modifica scale-ul unui sprite
	*/
	void setScaleDimension(int width , int height)
	{
		_dest->w = width;
		_dest->h = height;
	}

	/*
	* seteaza transparenta unui sprite
	*/
	void setOpacity(int opacity)
	{
		SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_texture, opacity);
	}

	/*
	* seteaza un chenar in jurul textului
	*/
	void setBorder(bool status)
	{
		_hasBorder = status;
	}

	/*
	* seleteza o anumita portiune din textura
	*/
	void setTexturePortion(int x, int y)
	{
		_src->x = x;
		_src->y = y;
	}

	/*
	* seteaza centrul de rotatie( rotatie realizata doar daca unghiul este diferit de 0)
	*/
	static void setCenter(SDL_Point point)
	{
		center = point;
	}

	/*
	*	seteaza statusul de obiect de pe mapa
	*/
	void setMapObjectStatus(bool status)
	{
		_isMapObject = status;
	}


	/*
	* seteaza statusul de urmarit de camera
	*/
	void setCameraFocus(bool status)
	{
		_isFollowed = status;
	}


	/*
	* getters
	*/

	/*
	* returneaza pozitia relativa la camera
	*/
	Vector2T<int> getPosition()
	{
		return Vector2T<int>(_dest->x, _dest->y);
	}

	/*
	* returneaza unghiul de desenare
	*/
	float getAngle()
	{
		return _angle;
	}

	/*
	* returneaza latimea unui sprite
	*/
	int getWidth()
	{
		return _dest->w;
	}

	/*
	* returneaza inaltimea unui sprite
	*/
	int getHeight()
	{
		return _dest->h;
	}

	/*
	* verica daca este sau nu in cadrul camerei
	*/
	void isOnCamera();


	void draw() override;

	void update() override;

};


