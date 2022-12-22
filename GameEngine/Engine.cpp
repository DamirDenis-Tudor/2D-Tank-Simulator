#include "Engine.h"

void Engine::initComponets()
{
	_components.emplace_back(new Map);

	_components.emplace_back(new SpecialObjectsManager);

	Director::setBuilder(new PlayerTank);

	Director::setBuilderAttributes("Type1", "ColorA");
	_components.push_back(Director::getResult());

	Director::setBuilder(new AiTank);

	Director::setBuilderAttributes("Type2", "ColorA");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type3", "ColorA");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type2", "ColorA");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type3", "ColorA");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type3", "ColorB");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type6", "ColorB");
	_components.push_back(Director::getResult());
	
	Director::setBuilderAttributes("Type3", "ColorB");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type6", "ColorB");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorB");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type2", "ColorC");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorC");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type5", "ColorC");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorC");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type5", "ColorC");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type2", "ColorD");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type7", "ColorD");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorD");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type7", "ColorD");
	_components.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorD");
	_components.push_back(Director::getResult());

	_components.emplace_back(new AnimationsHandler);

	_components.emplace_back(new InfoManager);

	_components.emplace_back(new MiniMap);
}

void Engine::draw()
{
	for (auto& i : _components)
	{
		i->draw();
	}
}

void Engine::update()
{
	for (auto& i : _components) 
	{
		i->update();
	}
}

Engine::Engine(const char* name, int width, int height, bool fullscreen, float framerate) : _framerate(framerate)
{
	InputManager::initInput();
	RendererManager::setRenderer(name, width, height, fullscreen);
	AssetsStorage::loadTiles("levels/level1scaled2.1.tmx");
	AssetsStorage::loadMiniMapTiles("assets/maps/miniMapTiles.tmx");
	AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");
	AssetsStorage::loadItems("assets/items/items.tmx");
	AssetsStorage::loadEffects("assets/sTanks/effects.tmx");
	Mediator::initSpawnZones(AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);
	MapSpaceManager::initNodes();
	CameraManager::init(AssetsStorage::_tileDim, AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);
	initComponets();

}

Engine::~Engine()
{
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
			if (SDLK_ESCAPE == event.key.keysym.sym)
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

		CameraManager::cameraSync();

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