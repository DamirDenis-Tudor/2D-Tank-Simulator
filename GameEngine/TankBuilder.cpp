#include"TankBuilder.h"

void TankBuilder::setTankParameters()
{
	/*
		Descriere :
			-> fiecare tip de tank are un set de animatii
			o viteza si un shooting time, unele mai coincid
			-> metoda are rolul de a facilita orice modificare
			legata de caracteristicile tank-ului
	*/

	if (_type == "Type1")
	{
		_attributes = new TankAttributes{ "Shot1","Impact1", { 0.42 , 0.42 } ,0.5 ,10 };
	}
	if (_type == "Type2")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.38 , 0.38 } ,0.4 ,8 };
	}
	if (_type == "Type3")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.35 , 0.35 } ,0.3 ,6 };
	}
	if (_type == "Type4")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.42 , 0.42 } ,0.35 , 7};
	}
	if (_type == "Type5")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.32 , 0.32 } ,0.38 ,6 };
	}
	if (_type == "Type6")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.38 , 0.38 } ,0.29 , 4 };
	}
	if (_type == "Type7")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.3 , 0.3 } , 0.6 , 12 };
	}
	if (_type == "Type8")
	{
		_attributes = new TankAttributes{ "Shot2","Impact2", { 0.42 , 0.42 } ,0.4 , 6 };
	}

	/*
	* de asemenea se va crea tabela de scor
	*/
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
	/*
	* comportament de tip player sau de tip AI
	*/
	setBehavior();


	map<string, SpriteComponent*> parts;
	parts.insert(pair<string, SpriteComponent* >("atracks", new SpriteComponent(AssetsStorage::_movebles[{"atracks"}])));
	parts.insert(pair<string, SpriteComponent* >("body", new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "body"}])));
	parts.insert(pair<string, SpriteComponent* >("cannon", new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "cannon"}])));

	/*
	* in functie de parametri principali primiti 
	* de builder sunt setati o serie de parametri 
	* mai specifici obietului
	*/
	setTankParameters();

	_result = new Tank(parts, _behavior, _attributes, _type, _color);

	if (playerIdentifier)
	{
		/*
		* in cazul in care avem un player construit
		* camera va fi seta defoult pe el(in cazul in care nu avem nic un player
		* camera este defoul in SpectatorMode)
		*/

		CameraManager::setFocusId(_result->_id);
		CameraManager::setSpectatorMode(false);
		Mediator::setMainPlayerId(_result->_id);

		/*
		* pentru player vom avea niste inforamtii ajutatoare pe ecran:
		* timpul de respawn si durata unuoi abilitati
		*/
		InfoManager::addInfo(to_string(_result->_id) + "respawn", new TextComponent(WHITE, 52, "", { RendererManager::_width / 2 , 0 } ));
		InfoManager::addInfo(to_string(_result->_id) + "abilityTimer", new TextComponent(WHITE, 42, "", { RendererManager::_width / 2 , 0 }));
	}
}