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
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.5 , 0.5 } ,1 ,10 };
	}
	if (_type == "Type2")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.4 ,3 };
	}
	if (_type == "Type3")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.35 , 0.35 } ,0.3 ,2 };
	}
	if (_type == "Type4")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.55 , 0.55 } ,0.2 ,1 };
	}
	if (_type == "Type5")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.7 ,4 };
	}
	if (_type == "Type6")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.4 ,2 };
	}
	if (_type == "Type7")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.45 , 0.45 } ,0.5 ,2 };
	}
	if (_type == "Type8")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.7 , 0.7 } ,0.2 ,1 };
	}

	Vector2T<int> scorePosition;
	if (_color == "Yellow")
	{
		InfoManager::addInfo(_color,
			new TextComponent(YELLOW , TextScoreBoardHeight 
				, _color + "Team:  ", YellowTeamScorePosition));

		scorePosition = YellowTeamScorePosition;
		scorePosition += Vector2T<int>{InfoManager::getDimension(_color)._x, 0};

		InfoManager::addInfo(_color + "Points",
			new TextComponent(YELLOW, TextScoreBoardHeight
				, "0" ,scorePosition ));
	}
	if (_color == "Green")
	{
		InfoManager::addInfo(_color,
			new TextComponent(GREEN, TextScoreBoardHeight
				, _color + "Team:  ", GreenTeamScorePosition));

		scorePosition = GreenTeamScorePosition;
		scorePosition += Vector2T<int>{InfoManager::getDimension(_color)._x, 0};

		InfoManager::addInfo(_color + "Points",
			new TextComponent(GREEN, TextScoreBoardHeight
				, "0", scorePosition));
	}
	if (_color == "Blue")
	{
		InfoManager::addInfo(_color,
			new TextComponent(BLUE, TextScoreBoardHeight
				, _color + "Team:  ", BlueTeamScorePosition));

		scorePosition = BlueTeamScorePosition;
		scorePosition += Vector2T<int>{InfoManager::getDimension(_color)._x, 0};

		InfoManager::addInfo(_color + "Points",
			new TextComponent(BLUE, TextScoreBoardHeight
				, "0", scorePosition));
	}
	if (_color == "Brown")
	{
		InfoManager::addInfo(_color,
			new TextComponent(BROWN, TextScoreBoardHeight
				, _color + "Team:  ", BrownTeamScorePosition));

		scorePosition = BrownTeamScorePosition;
		scorePosition += Vector2T<int>{InfoManager::getDimension(_color)._x, 0};

		InfoManager::addInfo(_color + "Points",
			new TextComponent(BROWN, TextScoreBoardHeight
				, "0", scorePosition));
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
		CameraManager::setSpectatorMode(false);
		Mediator::setMainPlayerId(_result->_id);
	}
}