#include "Engine.h"

void Engine::initComponets()
{
	_componets.emplace_back(new Map);

	Director::setBuilder(new PlayerTank);

	Director::setBuilderAttributes("Type1", "ColorA", { 64*3 ,64*6 });
	_componets.push_back(Director::getResult());
	
	Director::setBuilder(new AiTank);
	
	Director::setBuilderAttributes("Type2", "ColorA", { 64 * 10,64 * 7 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type2", "ColorA", { 64 * 18,64 * 10 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type3", "ColorB", { 64*45,64*4 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type4", "ColorB", { 64 * 38 ,64*2 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type5", "ColorB", {64 * 41,64 * 6});
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type5", "ColorC", { 64 * 12,64 * 27 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type6", "ColorC", {64 * 25 ,64 * 33});
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type7", "ColorC", { 64 * 23 ,64 * 31});
	_componets.push_back(Director::getResult());


	Director::setBuilderAttributes("Type8", "ColorD", { 64 *42,64 * 29 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorD", { 64 * 47,64 * 36 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorD", { 64 * 51,64 * 30 });
	_componets.push_back(Director::getResult());

	_componets.emplace_back(new AnimationsHandler);
	
	_componets.emplace_back(new MiniMap);
}

void Engine::draw() 
{
	for (auto& i : _componets)
	{
		i->draw();
	}
}

void Engine::update() 
{
	for (int i = 0; i < _componets.size(); i++)
	{
		_componets[i]->update();

		if (!_componets[i]->isActive())
		{
			delete _componets[i];
			_componets[i] = nullptr;
			_componets.erase(_componets.begin() + i);
			i--;
		}
	}
}

Engine::Engine(const char* name, int width, int height, bool fullscreen, float framerate) : _framerate(framerate)
{
	InputManager::initInput();
	RendererManager::setRenderer(name, width, height, fullscreen);
	AssetsStorage::loadTiles("levels/level1scaled2.1.tmx");
	AssetsStorage::loadMiniMapTiles("assets/maps/miniMapTiles.tmx");
	AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");
	AssetsStorage::loadEffects("assets/sTanks/effects.tmx");
	MapSpaceManager::initNodes();
	CameraManager::init(AssetsStorage::_tileDim, AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);
	initComponets();

}

Engine::~Engine()
{
	RendererManager::clear();
	InputManager::clear();
	AssetsStorage::clear();
	TimeManager::clear();
	MapSpaceManager::clear();
	Director::clear();
	for (auto& i : _componets)
	{
		delete i;
		i = nullptr;
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
		
		if (delay < 0 )
		{
			delay = 0;
		}


		SDL_Delay(delay);
	}
}