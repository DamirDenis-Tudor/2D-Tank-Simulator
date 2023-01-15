#include "Engine.h"
Engine::Engine(const char* name, int width, int height, bool fullscreen, float framerate) : _framerate(framerate)
{
	if (_framerate < 0 || _framerate > 60 || _framerate < 30)
	{
		throw("Eroare : framaterate invalid => jocul nu va mai functiona in parametri!");
	}
	InputManager::initInput();
	RendererManager::setRenderer(name, width, height, fullscreen);
	TextComponent::setFont("fonts/open-sans/Capsmall.ttf");

	AssetsStorage::loadMenu("assets/menu/menu.tmx");
	AssetsStorage::loadMiniTiles("assets/maps/miniMapTiles.tmx");
	AssetsStorage::loadSprites("assets/sTanks/tank.tmx");
	AssetsStorage::loadAbilities("assets/sTanks/abilities/abilities.tmx");
	AssetsStorage::loadEffects("assets/sTanks/effects.tmx");

	SoundManager::addBackgroundMusic("assets/sounds/menu/music.mp3", "music");
	SoundManager::addBackgroundMusic("assets/sounds/game/war.mp3", "war");

	SoundManager::addSoundEffect("assets/sounds/menu/switch.wav", "switch");
	SoundManager::addSoundEffect("assets/sounds/menu/click.wav", "click");

	SoundManager::addSoundEffect("assets/sounds/game/shooting1.wav", "fire");
	SoundManager::addSoundEffect("assets/sounds/game/shooting1.wav", "fire1");
	SoundManager::addSoundEffect("assets/sounds/game/releaseMine.wav", "releaseMine");
	SoundManager::addSoundEffect("assets/sounds/game/mineExplosion.wav", "mineExplosion");
	SoundManager::addSoundEffect("assets/sounds/game/ability.wav", "ability");
	SoundManager::addSoundEffect("assets/sounds/game/heal.wav", "heal");
	SoundManager::addSoundEffect("assets/sounds/game/tankExplosion.wav", "tankExplosion");
	SoundManager::addSoundEffect("assets/sounds/game/tankExplosion.wav", "tankExplosion1");
	SoundManager::addSoundEffect("assets/sounds/game/barrelExplosion.wav", "barrelExplosion");

	_menu = new Menu;
}

Engine::~Engine()
{
	delete _menu;
	_menu = nullptr;

	for (auto& i : _components)
	{
		delete i;
		i = nullptr;
	}

	RendererManager::clear();
	InputManager::clear();
	AssetsStorage::clear();
	TimeManager::clear();
	Director::clear();
	MapSpaceManager::clear();
	SoundManager::clear();
}

void Engine::initComponets()
{
	_components.emplace_back(new Map);

	_components.emplace_back(new SpecialObjectsManager);

	initTanks(3 , Menu::getPlayerType(), Menu::getPlayerTeam());

	_components.emplace_back(new AnimationsHandler);

	_components.emplace_back(new MiniMap);

	_components.emplace_back(new InfoManager);
}

void Engine::initGameMap(const char* source)
{
	AssetsStorage::loadMap(source);
	CameraManager::init(AssetsStorage::_tileDim, AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);
	Mediator::init(AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);
	MapSpaceManager::initNodes();
}

void Engine::clearGameComponets()
{
	for (auto& i : _components)
	{
		delete i;
		i = nullptr;
	}
	_components.clear();;
	MapSpaceManager::clear();
	AssetsStorage::clearMap();
	CameraManager::clear();
	Mediator::clear();
}

void Engine::initTanks(int teamMembers, string playerType, string playerTeam)
{
	/*
	* cream playerul
	*/
	if (playerType != "NONE")
	{
		Director::setBuilder(new PlayerTank);
		Director::setBuilderAttributes(playerType, playerTeam);
		_components.push_back(Director::getResult());
	}

	Director::setBuilder(new AiTank);
	for (int i = 0; i < teamMembers; i++)
	{
		/*
		* se face creea cu un tank mai putin 
		*/
		if (playerTeam == "Yellow" && i > teamMembers - 2)
		{
			break;
		}
		Director::setBuilderAttributes("Type" + to_string(rand() % 4 + rand() % 4 + 1), "Yellow");
		_components.push_back(Director::getResult());

	}

	for (int i = 0; i < teamMembers; i++)
	{
		if (playerTeam == "Blue" && i > teamMembers - 2)
		{
			break;
		}
		Director::setBuilderAttributes("Type" + to_string(rand() % 4 + rand() % 4 + 1), "Blue");
		_components.push_back(Director::getResult());
	}

	for (int i = 0; i < teamMembers; i++)
	{
		if (playerTeam == "Green" && i > teamMembers - 2)
		{
			break;
		}
		Director::setBuilderAttributes("Type" + to_string(rand() % 4 + rand() % 4 + 1), "Green");
		_components.push_back(Director::getResult());
	}

	for (int i = 0; i < teamMembers; i++)
	{
		if (playerTeam == "Brown" && i > teamMembers - 2)
		{
			break;
		}
		Director::setBuilderAttributes("Type" + to_string(rand() % 4 + rand() % 4 + 1), "Brown");
		_components.push_back(Director::getResult());
	}
}

void Engine::draw()
{
	if (_menu->isActive())
	{
		_menu->draw();
		return;
	}

	for (auto& i : _components)
	{
		i->draw();
	}
}

void Engine::update()
{
	/*
	* daca este apasat de la tastatura butonul escape
	* si meniul nu este activat => activarea meniului
	*/
	if (InputManager::_escape && !_menu->isActive())
	{
		_menu->enable();
		SoundManager::playBackgroundMusic("music");
	}

	/*
	* daca meniul este activ
	*/
	if (_menu->isActive())
	{
		/*
		* updatam meniul
		*/
		_menu->update();

		return;
	}

	/*
	* daca meniul are a inregistrat comanda de incarcare 
	* a unei mape
	*/
	if (Menu::getMapName() != "NONE")
	{
		/*
		* stergem componentele legate de 
		* actuala desfasurare a jocului
		*/
		clearGameComponets();

		/*
		* creeam timer-ul pentru joc si avem sa eliminam 
		* timerul aferent jocului precedent
		*/
		TimeManager::removeTimer(to_string(_id));
		TimeManager::createTimer(to_string(_id), 60);
		InfoManager::addInfo(to_string(_id), new TextComponent(WHITE, 54));
		TimeManager::getTimer(to_string(_id))->resetTimer();

		InfoManager::addInfo("mouse", new TextComponent(BLACK, 64, " x "));

		/*
		* selectam tipul mapei incarcand 
		* mapa si spriturile ei aferente
		*/
		if (Menu::getMapName() == "FOOTBALL EXTRATIME")
		{
			initGameMap("levels/football.tmx");
		}
		else if (Menu::getMapName() == "DESSERT COWBOYS")
		{
			initGameMap("levels/desert.tmx");
		}
		else if (Menu::getMapName() == "MARS SPACEWAR")
		{
			initGameMap("levels/space.tmx");
		}

		/*
		*	initializam componentele 
		*/
		initComponets();

		/*
		* task-ul este efectuat
		*/
		Menu::setMapName("NONE");
	}

	/*
	* daca timerul jocului este in functiune
	*/
	if (TimeManager::getTimer(to_string(_id))->isTimerWorking())
	{
		/*
		* actualizam textul cu reminder-ul
		*/
		InfoManager::setText(to_string(_id), "Match ends in " +
			to_string(TimeManager::getTimer(to_string(_id))->getRemainingTime()));

		/*
		* setam pozitia in centru
		*/
		InfoManager::setCameraPosition(to_string(_id),
			Vector2T<int>{ RendererManager::_width / 2 - InfoManager::getDimension(to_string(_id))._x / 2, 64  });

		/*
		* daca timer-ul este mai mic de 15 secunde ii schimbam culoarea
		*/
		if (TimeManager::getTimer(to_string(_id))->getRemainingTime() < 15)
		{
			InfoManager::setColor(to_string(_id), RED);
		}

		/*
		* sincronizam camera
		*/
		CameraManager::cameraSync();

		/*
		* actualizam componentele
		*/
		for (auto& i : _components)
		{
			i->update();
		}

		InfoManager::setCameraPosition("mouse", InputManager::mousePos - InfoManager::getDimension("mouse") / 2);
	}
	else
	{
		/*
		* daca timer-ul s-a oprit stabilesc un deznodamant
		*/
		string teamWinning = Mediator::getTeamWithHighestScore();
		string displayText;

		if (teamWinning != "NONE")
		{
			if (!CameraManager::getSpectatorMode() && teamWinning == Mediator::getColorTeam(CameraManager::getFocusId()))
			{
				displayText ="Your team has won the game !";
			}
			else
			{
				displayText = teamWinning + " has won the game !";
			}
		}
		else
		{
			displayText = "Game is tied ! ";
		}

		/*
		* setez textul corespunzator deznodamanatului
		*/
		InfoManager::addInfo(to_string(_id) + "over", new TextComponent(WHITE, 54, displayText + " Press ESC ... "));
		InfoManager::setCameraPosition(to_string(_id) + "over",
			{ RendererManager::_width / 2 - InfoManager::getDimension(to_string(_id) + "over")._x / 2
			, RendererManager::_heigth / 2 });
	}
}

void Engine::run()
{
	static bool quitGame = false;
	SDL_Event event;

	double time1, time2;
	double delay;

	TimeManager::setDeltatime(1 / _framerate * 1000);
	Timer::setDeltatime(1 / _framerate * 1000);

	while (false == quitGame)
	{
		time1 = SDL_GetTicks64();
		while (SDL_PollEvent(&event) != 0)
		{
			if (Menu::_endGame)
			{
				quitGame = true;
			}
			switch (event.type)
			{
			case SDL_KEYDOWN:
				InputManager::keyPressed(event);
				break;
			case SDL_KEYUP:
				InputManager::keyReleased(event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				InputManager::mouseButtonPressed(event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				InputManager::mouseButtonReleased(event.button);
				break;
			default:
				break;
			}
		}

		SDL_RenderClear(RendererManager::_renderer);

		InputManager::update();

		update();

		draw();

		SDL_RenderPresent(RendererManager::_renderer);

		time2 = SDL_GetTicks64();

		delay = 1 / _framerate * 1000 - time2 + time1;

		if (delay < 0)
		{
			delay = 0;
		}

		SDL_Delay(delay);
	}
}