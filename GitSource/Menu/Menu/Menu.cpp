#include "Menu.h"
#include "SoundManager.h"

bool Menu::_endGame = false;
string Menu::_mapName = "NONE";
float Menu::_dificultyVal = 1;
string Menu::_playerTeam = "NONE";
string Menu::_playerType = "NONE";

Menu::Menu()
{
	SoundManager::playBackgroundMusic("music");
	/*
	* creeam un timer pentru switch-ul dintre scene
	*/
	TimeManager::createTimer(to_string(_id), 0.3);
	TimeManager::getTimer(to_string(_id))->resetTimer();

	TimeManager::createTimer(to_string(_id) + "selection", 5);

	SDL_ShowCursor(SDL_DISABLE);

	/*
	* intilizam background-urile
	*/
	_backgrounds.insert(pair<string, SpriteComponent*>("BACKGROUND", new SpriteComponent(AssetsStorage::_menuItems["background"])));
	_backgrounds.insert(pair<string, SpriteComponent*>("FOOTBALL EXTRATIME", new SpriteComponent(AssetsStorage::_menuItems["football"])));
	_backgrounds.insert(pair<string, SpriteComponent*>("DESSERT COWBOYS", new SpriteComponent(AssetsStorage::_menuItems["dessert"])));
	_backgrounds.insert(pair<string, SpriteComponent*>("MARS SPACEWAR", new SpriteComponent(AssetsStorage::_menuItems["mars"])));

	/*
	* initializam previewrile pentru tank
	*/
	_previews.insert(pair<string, SpriteComponent*>("zankYellow", new SpriteComponent(AssetsStorage::_menuItems["YELLOW TEAM"])));
	_previews.insert(pair<string, SpriteComponent*>("zankBlue", new SpriteComponent(AssetsStorage::_menuItems["BLUE TEAM"])));
	_previews.insert(pair<string, SpriteComponent*>("zankBrown", new SpriteComponent(AssetsStorage::_menuItems["BROWN TEAM"])));
	_previews.insert(pair<string, SpriteComponent*>("zankGreen", new SpriteComponent(AssetsStorage::_menuItems["GREEN TEAM"])));


	for (auto& background : _backgrounds)
	{
		if (background.first != "BACKGROUND")
		{
			background.second->disable();
		}
		background.second->setCameraPosition({ RendererManager::_width / 2 - background.second->getWidth() / 2
			,RendererManager::_heigth / 2 - background.second->getHeight() / 2 });
	}

	for (auto& preview : _previews)
	{
		preview.second->disable();
	}

	/*
	* creemm scenele cu butoanele aferent
	*/

	/*
	* scena main
	*/
	_scenes.push_back(new MenuScene("Main",
		{
		  new TextButton("2D TANK" , GOLD , 92 , 1) , // nu va fi hover si va fi activ
		  new TextButton("SIMULATOR" , GOLD , 92 , 2) ,
		  new TextButton("" , WHITE , 64 , 6 , false , false) , // folosit pe poste de delimitare dintre butoane si titlu
		  new TextButton("CONTINUE" , WHITE , 64 , 7 , false , false) ,
		  new TextButton("NEW GAME" , WHITE , 64 , 8 , true) ,
		  new TextButton("QUIT GAME" , WHITE , 64 , 9) }));

	/*
	* scena de selectare a mapelor
	*/
	_scenes.push_back(new MenuScene("Load",
		{
		  new TextButton("SELECT LEVEL" , WHITE , 92 , 1 , false , true) , // nu va fi hover si va fi activ
		  new TextButton("" , WHITE , 64 , 7 , false , false) , // // folosit pe poste de delimitare dintre butoane si titlu
		  new TextButton("MARS SPACEWAR" , WHITE , 64 , 7 , true) ,
		  new TextButton("FOOTBALL EXTRATIME" , WHITE , 64 , 8) ,
		  new TextButton("DESSERT COWBOYS" , WHITE , 64 , 9) ,
		  new TextButton("BACK" , WHITE , 64 , 14) , }
	));

	/*
	* scena de seletare a dificultatii
	*/
	_scenes.push_back(new MenuScene("Dificulty",
		{
		  new TextButton("SELECT DIFICULTY" , WHITE , 92 , 1 , false , true) , // nu va fi hover si va fi activ
		  new TextButton("" , WHITE , 64 , 7 , false , false) , // // folosit pe poste de delimitare dintre butoane si titlu
		  new TextButton("EASY" , WHITE , 64 , 7 , true) ,
		  new TextButton("NORMAL" , WHITE , 64 , 8) ,
		  new TextButton("HARD" , WHITE , 64 , 9) ,
		  new TextButton("BACK" , WHITE , 64 , 14) }
	));

	/*
	* scena de selectare a echipei
	*/
	_scenes.push_back(new MenuScene("Team",
		{
		  new TextButton("SELECT TEAM" , WHITE , 92 , 1 , false , true) ,
		  new TextButton("" , WHITE , 64 , 5 , false , false) , // // folosit pe poste de delimitare dintre butoane si titlu
		  new TextButton("SPECTATOR MODE" , WHITE , 64 , 6 , true) , // va fi hover
		  new TextButton("YELLOW TEAM" , WHITE , 64 , 7) ,
		  new TextButton("BLUE TEAM" , WHITE , 64 , 8) ,
		  new TextButton("GREEN TEAM" , WHITE , 64 , 9) ,
		  new TextButton("BROWN TEAM" , WHITE , 64 , 10) ,
		  new TextButton("BACK" , WHITE , 64 , 14) }
	));

	/*
	* scena de selectare a tank-ului
	*/
	_scenes.push_back(new MenuScene("Type",
		{
		  new TextButton("SELECT TANK" , WHITE , 92 , 1 , false , true) ,
		  new TextButton("" , WHITE , 64 , 7 , false , false) , // // folosit pe poste de delimitare dintre butoane si titlu
		  new TextButton("TACTICAL" , WHITE , 64 , 5 , true) , // va fi hover
		  new TextButton("LAZER" , WHITE , 64 , 6) ,
		  new TextButton("TYPICAL" , WHITE , 64 , 7) ,
		  new TextButton("SNIPER" , WHITE , 64 , 8) ,
		  new TextButton("PLASMA" , WHITE , 64 , 9) ,
		  new TextButton("SHOTGUN" , WHITE , 64 , 10) ,
		  new TextButton("HEAVY" , WHITE , 64 , 11) ,
		  new TextButton("FIREBALL" , WHITE , 64 , 12) ,
		  new TextButton("BACK" , WHITE , 64 , 14) }
	));
}


Menu::~Menu()
{
	for (auto& background : _backgrounds)
	{
		background.second->setSrcTextNullPtr();
		delete background.second;
		background.second = nullptr;
	}

	_backgrounds.clear();

	for (auto& preview : _previews)
	{
		preview.second->setSrcTextNullPtr();
		delete preview.second;
		preview.second = nullptr;
	}

	_previews.clear();

	for (auto& scene : _scenes)
	{
		delete scene;
		scene = nullptr;
	}
}

void Menu::setSceneStatus(string name, bool status)
{
	for (auto& scene : _scenes)
	{
		if (scene->getName() != name) continue;

		status ? scene->enable() : scene->disable();

		break;
	}
}

void Menu::setButtonSceneStatus(string name, string button, bool status)
{
	for (auto& scene : _scenes)
	{
		if (scene->getName() != name) continue;

		scene->setButtonStatus(button, status);

		break;
	}
}

void Menu::menuLogic(MenuScene* scene)
{
	/*
	* scenea de main
	*/
	if (scene->getName() == "Main")
	{
		for (auto& preview : _previews)
		{
			preview.second->disable();
		}
		/*
		* daca este apasat butonul de CONTINUE si timer-ul permite acest lucru
		*/
		if (scene->getPressedButtonName() == "CONTINUE" && !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			* resetam timer-ul
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* resetam apasarea butonului
			*/
			scene->resetPressedButton();

			/*
			* punem pe pauza muzica de meniu
			*/
			SoundManager::pauseBackgroundMusic("music");
			SoundManager::playBackgroundMusic("war");

			/*
			* dezativam meniul
			*/
			disable();
		}
		/*
		* daca este apasat butonul de NEW GAME si timer-ul permite acest lucru
		*/
		else if (scene->getPressedButtonName() == "NEW GAME" && !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			* resetam timer-ul
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* resetam apasarea butonului
			*/
			scene->resetPressedButton();

			/*
			* dezactivam scene curenta
			*/
			scene->disable();

			/*
			* activam scena urmatoare
			*/
			setSceneStatus("Dificulty", true);
		}
		/*
		* daca este apasat QUIT GAME se activeaza
		* variabila corespunzatoare terminarii jocului
		*/
		else if (scene->getPressedButtonName() == "QUIT GAME")
		{
			_endGame = true;
		}
	}
	/*
	* scena de selectare a dificultatii
	*/
	else if (scene->getName() == "Dificulty")
	{
		/*
		* daca se apasa unul din butoanele ce reprezita dificultatea
		* si timerul permite acest lucru
		*/
		if (scene->getPressedButtonName() != "BACK" && scene->getPressedButtonName() != "NONE"
			&& !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			* se reseteaza timer-ul
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* in functie de dificultate se seteaza
			* variabila corespuzatoare aplicarii dificultatii
			*/
			if (scene->getPressedButtonName() == "EASY")
			{
				_dificultyVal = 1;
			}
			else if (scene->getPressedButtonName() == "NORMAL")
			{
				_dificultyVal = 1.15;
			}
			else if (scene->getPressedButtonName() == "HARD")
			{
				_dificultyVal = 1.35;
			}

			/*
			* se reseteaza butonul apasat
			*/
			scene->resetPressedButton();

			/*
			* se reseteaza apasarea butonului
			*/
			scene->resetPressedButton();

			/*
			* se dezactiveaza scena
			*/
			scene->disable();

			/*
			* se activeaza scena urmatoare
			*/
			setSceneStatus("Load", true);
		}
		/*
		*	daca se apasa butonul BACK sau ESC(de la tastatura) si timer-ul permite acest lucru)
		*/
		else if ((scene->getPressedButtonName() == "BACK" || InputManager::_escape)
			&& !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			* se reseteaza timerul
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* se reseteaza apasarea butonului
			*/
			scene->resetPressedButton();

			/*
			* se dezactiveaza scena
			*/
			scene->disable();

			/*
			* se activeaza scena precedenta
			*/
			setSceneStatus("Main", true);
		}

	}

	/*
	* meniul de load map
	*/
	else if (scene->getName() == "Load")
	{
		for (auto& preview : _previews)
		{
			preview.second->disable();
		}

		/*
		* selectare previwn mapa
		*/
		if (scene->getHoveredButtonName() == "FOOTBALL EXTRATIME")
		{
			/*
			* activare
			*/
			_backgrounds["DESSERT COWBOYS"]->disable();
			_backgrounds["MARS SPACEWAR"]->disable();
			_backgrounds["FOOTBALL EXTRATIME"]->enable();
		}
		else if (scene->getHoveredButtonName() == "DESSERT COWBOYS")
		{
			_backgrounds["FOOTBALL EXTRATIME"]->disable();
			_backgrounds["DESSERT COWBOYS"]->enable();
			_backgrounds["MARS SPACEWAR"]->disable();
		}
		else if(scene->getHoveredButtonName() == "MARS SPACEWAR")
		{
			_backgrounds["FOOTBALL EXTRATIME"]->disable();
			_backgrounds["DESSERT COWBOYS"]->disable();
			_backgrounds["MARS SPACEWAR"]->enable();
		}

		/*
		* daca selectez o mapa si timerul permite acest lucru
		*/
		if (scene->getPressedButtonName() != "BACK" && scene->getPressedButtonName() != "NONE"
			&& !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* salvez numele mapei de incarcat
			*/
			_mapName = scene->getPressedButtonName();

			/*
			* resetam apasarea butonului
			*/
			scene->resetPressedButton();

			/*
			* dezactivam scena
			*/
			scene->disable();

			/*
			* activam scena urmatoare
			*/
			setSceneStatus("Team", true);
		}
		/*
		*	daca se apasa butonul BACK sau ESC(de la tastatura) si timer-ul permite acest lucru)
		*/
		else if ((scene->getPressedButtonName() == "BACK") && !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			TimeManager::getTimer(to_string(_id))->resetTimer();

			scene->resetPressedButton();

			scene->disable();

			/*
			* revin la scena anterioara
			*/
			setSceneStatus("Dificulty", true);

			/*
			* daca revin la scena aterioara dezactivez previeurile pentru mapa
			*/
			_backgrounds["DESSERT COWBOYS"]->disable();
			_backgrounds["FOOTBALL EXTRATIME"]->disable();
			_backgrounds["MARS SPACEWAR"]->disable();
		}
	}

	/*
	* scena de selectare a echipei
	*/
	else if (scene->getName() == "Team")
	{
		/*
		* daca selectez o echipa si timer-ul permite acest lucru
		*/
		if (scene->getPressedButtonName() != "BACK" && scene->getPressedButtonName() != "NONE"
			&& scene->getPressedButtonName() != "SPECTATOR MODE"
			&& !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* salvam selectia faculta
			*/
			if (scene->getPressedButtonName() == "YELLOW TEAM")
			{
				_playerTeam = "Yellow";

			}
			else if (scene->getPressedButtonName() == "BLUE TEAM")
			{
				_playerTeam = "Blue";
			}
			else if (scene->getPressedButtonName() == "BROWN TEAM")
			{
				_playerTeam = "Brown";
			}
			else if (scene->getPressedButtonName() == "GREEN TEAM")
			{

				_playerTeam = "Green";
			}

			/*
			* dezactivam scena
			*/
			scene->disable();

			/*
			* activam urmatoarea scena
			*/
			setSceneStatus("Type", true);

			/*
			* resetam butonul apasat
			*/
			scene->resetPressedButton();
		}

		/*
		* daca este selectata optiunea de spectator mode si timer-ul ii permite
		*/
		else if (scene->getPressedButtonName() == "SPECTATOR MODE" && !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			/*
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* dezactivam scena
			*/
			scene->disable();

			/*
			* resetam butonul apasat
			*/
			scene->resetPressedButton();

			/*
			* nota: acesta este ultima scena din ierarhia de scene
			* vom seta scena main activa, aceasta deservind meniului de pauza
			*/
			setSceneStatus("Main", true);

			/*
			* fiind meniu de pauza are activat butonul de continue
			*/
			setButtonSceneStatus("Main", "CONTINUE", true);

			/*
			* setam varibilele necesare pentru a intra in spectator MODE
			*/
			_playerTeam = "NONE";
			_playerType = "NONE";


			/*
			* daca sunt in spectator mode si trec la scena urmatoare 
			* dezactivez preview-urile
			*/
			_backgrounds["DESSERT COWBOYS"]->disable();
			_backgrounds["FOOTBALL EXTRATIME"]->disable();
			_backgrounds["MARS SPACEWAR"]->disable();

			/*
			* punem pe pauza muzica de meniu
			*/
			SoundManager::pauseBackgroundMusic("music");
			SoundManager::playBackgroundMusic("war");

			/*
			* dezactivam meniul
			*/
			disable();
		}

		/*
		*	daca se apasa butonul BACK sau ESC(de la tastatura) si timer-ul permite acest lucru)
		*/
		else if ((scene->getPressedButtonName() == "BACK") && !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			TimeManager::getTimer(to_string(_id))->resetTimer();

			scene->resetPressedButton();
			scene->disable();

			/*
			* activez scena precedenta
			*/
			setSceneStatus("Load", true);
		}

		/*
		* preview-ul pentru tank-uri
		*/
		if (scene->getHoveredButtonName() == "YELLOW TEAM")
		{
			/*
			* seetam pozitia
			*/
			_previews["zankYellow"]->setCameraPosition(_backgrounds[_mapName]->getPosition()
				+ Vector2T<int>{_previews["zankYellow"]->getWidth() / 2, _previews["zankYellow"]->getHeight() / 2 });

			/*
			* dezativam preview-urile de tank
			*/
			for (auto& preview : _previews)
			{
				preview.second->disable();
			}

			/*
			* si activize preview-ul aferent
			*/
			_previews["zankYellow"]->enable();
		}
		else if (scene->getHoveredButtonName() == "GREEN TEAM")
		{
			_previews["zankGreen"]->setCameraPosition(_backgrounds[_mapName]->getPosition()
				+ Vector2T<int>{ _previews["zankGreen"]->getWidth() / 2,
				-2 * _previews["zankGreen"]->getHeight() + _previews["zankGreen"]->getHeight() / 2 + _backgrounds[_mapName]->getHeight()});

			for (auto& preview : _previews)
			{
				preview.second->disable();
			}
			_previews["zankGreen"]->enable();
		}
		else if (scene->getHoveredButtonName() == "BLUE TEAM")
		{
			_previews["zankBlue"]->setCameraPosition(_backgrounds[_mapName]->getPosition()
				+ Vector2T<int>{ -2 * _previews["zankBlue"]->getWidth() + _previews["zankBlue"]->getWidth() / 2 + _backgrounds[_mapName]->getWidth(),
				_previews["zankBlue"]->getHeight() / 2 });

			for (auto& preview : _previews)
			{
				preview.second->disable();
			}
			_previews["zankBlue"]->enable();
		}
		else if (scene->getHoveredButtonName() == "BROWN TEAM")
		{
			_previews["zankBrown"]->setCameraPosition(_backgrounds[_mapName]->getPosition()
				+ Vector2T<int>{ -2 * _previews["zankBrown"]->getWidth() + _previews["zankBrown"]->getWidth() / 2 + _backgrounds[_mapName]->getWidth(),
				-2 * _previews["zankBrown"]->getHeight() + _previews["zankBrown"]->getHeight() / 2 + _backgrounds[_mapName]->getHeight()});

			for (auto& preview : _previews)
			{
				preview.second->disable();
			}

			_previews["zankBrown"]->enable();
		}
		else
		{
			for (auto& preview : _previews)
			{
				preview.second->disable();
			}
		}

	}

	/*
	* scena de selectare a tipului tank-ului
	*/
	else if (scene->getName() == "Type")
	{
		/*
		* daca este apasat un buton corepunzator tipului si timer-ul permite acest lucru
		*/
		if (scene->getPressedButtonName() != "BACK" && scene->getPressedButtonName() != "NONE"
			&& !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* salvam selectia faculta
			*/
			if (scene->getPressedButtonName() == "TACTICAL")
			{
				_playerType = "Type1";
			}
			else if (scene->getPressedButtonName() == "LAZER")
			{
				_playerType = "Type2";
			}
			else if (scene->getPressedButtonName() == "TYPICAL")
			{
				_playerType = "Type3";
			}
			else if (scene->getPressedButtonName() == "SNIPER")
			{
				_playerType = "Type4";
			}
			else if (scene->getPressedButtonName() == "PLASMA")
			{
				_playerType = "Type5";
			}
			else if (scene->getPressedButtonName() == "SHOTGUN")
			{
				_playerType = "Type6";
			}
			else if (scene->getPressedButtonName() == "HEAVY")
			{
				_playerType = "Type7";
			}
			else if (scene->getPressedButtonName() == "FIREBALL")
			{
				_playerType = "Type8";
			}

			/*
			* dezacivam scena
			*/
			scene->disable();

			/*
			* nota: acesta este ultima scena din ierarhia de scene
			* vom seta scena main activa, aceasta deservind meniului de pauza
			*/
			setSceneStatus("Main", true);

			/*
			* fiind meniu de pauza are activat butonul de continue
			*/
			setButtonSceneStatus("Main", "CONTINUE", true);

			/*
			* resetam butonul apasat
			*/
			scene->resetPressedButton();

			_backgrounds["DESSERT COWBOYS"]->disable();
			_backgrounds["FOOTBALL EXTRATIME"]->disable();
			_backgrounds["MARS SPACEWAR"]->disable();

			/*
			* punem pe pauza muzica de meniu
			*/
			SoundManager::pauseBackgroundMusic("music");
			SoundManager::playBackgroundMusic("war");

			/*
			* dezactivam meniul
			*/
			disable();
		}
		/*
		*	daca se apasa butonul BACK sau ESC(de la tastatura) si timer-ul permite acest lucru)
		*/
		else if ((scene->getPressedButtonName() == "BACK") && !TimeManager::getTimer(to_string(_id))->isTimerWorking())
		{
			TimeManager::getTimer(to_string(_id))->resetTimer();

			scene->resetPressedButton();
			scene->disable();

			/*
			* revenim la scena precedenta
			*/
			setSceneStatus("Team", true);

			_previews[getPreviewTank()]->enable();
		}


		/*
		* seletam tank-ul corespunzator din sprite sheet
		*/
		int x = scene->getHoveredButtonOrder() - 2, y = 0;

		if (scene->getHoveredButtonOrder() - 2 >= 4)
		{
			x = scene->getHoveredButtonOrder() - 2 - 4;
			y = 1;
		}

		_previews[getPreviewTank()]->selectSpriteRectagle(x, y);
		
	}
}

string Menu::getMapName()
{
	return _mapName;
}

string Menu::getPlayerTeam()
{
	return _playerTeam;
}

string Menu::getPlayerType()
{
	return _playerType;
}

void Menu::setMapName(string name)
{
	_mapName = name;
}

float Menu::getDifficultyVar()
{
	return _dificultyVal;
}

void Menu::update()
{
	for (auto& background : _backgrounds)
	{
		background.second->update();
	}

	for (auto& preview : _previews)
	{
		preview.second->update();
	}


	for (auto& scene : _scenes)
	{
		if (!scene->isActive()) continue;

		scene->update();
		menuLogic(scene);
	}
}

void Menu::draw()
{
	for (auto& background : _backgrounds)
	{
		background.second->draw();
	}

	for (auto& preview : _previews)
	{
		preview.second->draw();
	}

	for (auto& scene : _scenes)
	{
		if (!scene->isActive()) continue;

		scene->draw();
	}
}
