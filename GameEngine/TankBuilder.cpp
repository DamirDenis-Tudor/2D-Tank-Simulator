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
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.1 ,5 };
	}
	if (_type == "Type2")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
	if (_type == "Type3")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
	if (_type == "Type4")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
	if (_type == "Type5")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
	if (_type == "Type6")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
	if (_type == "Type7")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
	if (_type == "Type8")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.2 ,2 };
	}
}

void TankBuilder::build()
{
	setBehavior();

	map<string, SpriteComponent*> parts;
	parts.insert(pair<string, SpriteComponent* >("atracks", new SpriteComponent(AssetsStorage::_movebles[{"atracks"}])));
	parts.insert(pair<string, SpriteComponent* >("body", new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "body"}])));
	parts.insert(pair<string, SpriteComponent* >("cannon", new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "cannon"}])));

	setTankParameters();

	_result = new Tank(parts, _behavior, _attributes, _type, _color);

	if (playerIdentifier)
	{
		CameraManager::setFocusId(_result->_id);
	}
}