#include"TankBuilder.h"

void TankBuilder::setTankParameters()
{
	/*
		Descriere :
			-> fiecare tip de tank are un set de animatii
			o viteza si un shooting time, unele mai coincid
			-> metoda are rolul de a facilita orice modificare
			legata de caracteristicile tank-ului

			Nota:
				-> initial am vrut sa vin cu valorile astea prestabilite
					din fisierul xml, dar am divizat sprite-urile de tank-uri
					de cele de efecte si de aici si solutia asta
	*/

	if (_type == "Type1")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.4 , 0.4 };
		_shotingTime = 0.3;
	}
	if (_type == "Type2")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.2 , 0.2 };
		_shotingTime = 0.3;
	}
	if (_type == "Type3")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.24 , 0.24 };
		_shotingTime = 1.2;
	}
	if (_type == "Type4")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.22 , 0.22 };
		_shotingTime = 0.5;
	}
	if (_type == "Type5")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.355 , 0.355 };
		_shotingTime = 1.0;
	}
	if (_type == "Type6")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.267 , 0.267 };
		_shotingTime = 0.7;
	}
	if (_type == "Type7")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.345 , 0.345 };
		_shotingTime = 0.6;
	}
	if (_type == "Type8")
	{
		_shotingAnim = "Shot1";
		_impactAnim = "BigExplosion";
		_velocity = { 0.35 , 0.35 };
		_shotingTime = 0.5;
	}
}

void TankBuilder::build()
{
	setBehavior();

	SpriteComponent* tracks = new SpriteComponent(AssetsStorage::_movebles[{"tracks"}]);
	SpriteComponent* body = new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "body"}]);
	SpriteComponent* cannon = new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "cannon"}]);

	setTankParameters();

	_result = new Tank(tracks, body, cannon, _behavior, _position , _velocity 
		,_shotingTime , _type , _color , _shotingAnim , _impactAnim);

	if (playerIdentifier)
	{
		CameraManager::setFocusId(_result->_id);
	}
}