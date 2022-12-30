#include "Engine.h"

void Engine::initComponets()
{
	_menu = new MenuScene;

	_components.emplace_back(new Map);

	_components.emplace_back(new SpecialObjectsManager);

	// numar maxim de membri 8
	// Type1 , Type2 ... Type8
	// Yellow , Blue , Green, Brown
	initTanks(4, "Type1", "Brown");
	//initTanks(4);


	_components.emplace_back(new AnimationsHandler);

	_components.emplace_back(new MiniMap);

	_components.emplace_back(new InfoManager);
}

void Engine::initTanks(int teamMembers, string playerType, string playerTeam)
{
	if (playerType != "NONE")
	{
		Director::setBuilder(new PlayerTank);
		Director::setBuilderAttributes(playerType, playerTeam);
		_components.push_back(Director::getResult());
	}

	Director::setBuilder(new AiTank);
	for (int i = 0; i < teamMembers; i++)
	{
		Director::setBuilderAttributes("Type" + to_string(rand() % 8 + 1), "Yellow");
		_components.push_back(Director::getResult());
		if (playerTeam == "Yellow" && i == teamMembers - 2)
		{
			break;
		}
	}

	for (int i = 0; i < teamMembers; i++)
	{
		Director::setBuilderAttributes("Type" + to_string(rand() % 8 + 1), "Blue");
		_components.push_back(Director::getResult());
		if (playerTeam == "Blue" && i == teamMembers - 2)
		{
			break;
		}
	}

	for (int i = 0; i < teamMembers; i++)
	{
		Director::setBuilderAttributes("Type" + to_string(rand() % 8 + 1), "Green");
		_components.push_back(Director::getResult());
		if (playerTeam == "Green" && i == teamMembers - 2)
		{
			break;
		}
	}

	for (int i = 0; i < teamMembers; i++)
	{
		Director::setBuilderAttributes("Type" + to_string(rand() % 8 + 1), "Brown");
		_components.push_back(Director::getResult());
		if (playerTeam == "Brown" && i == teamMembers - 2)
		{
			break;
		}
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
	if (InputManager::_escape && !_menu->isActive())
	{
		_menu->enable();
	}
	if (_menu->isActive())
	{
		_menu->update();
		return;
	}
	CameraManager::cameraSync();
	for (auto& i : _components)
	{
		i->update();
	}
}

Engine::Engine(const char* name, int width, int height, bool fullscreen, float framerate) : _framerate(framerate)
{
	InputManager::initInput();
	RendererManager::setRenderer(name, width, height, fullscreen);

	TextComponent::setFont("fonts/open-sans/OpenSans-Bold.ttf");



	/*
	*   mai este si mapa asta
		AssetsStorage::loadTiles("levels/football.tmx");
	*/
	AssetsStorage::loadTiles("levels/desert.tmx");

	AssetsStorage::loadMiniTiles("assets/maps/miniMapTiles.tmx");
	AssetsStorage::loadSprites("assets/sTanks/tank.tmx");
	AssetsStorage::loadAbilities("assets/sTanks/abilities/abilities.tmx");
	AssetsStorage::loadEffects("assets/sTanks/effects.tmx");

	Mediator::init(AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);

	MapSpaceManager::initNodes();

	CameraManager::init(AssetsStorage::_tileDim, AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);


	initComponets();

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
			if (MenuScene::endGame)
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
				InputManager::clicked = true;
				break;
			case SDL_MOUSEBUTTONUP:
				InputManager::clicked = false;
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