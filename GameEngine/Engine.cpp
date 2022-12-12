#include "Engine.h"

void Engine::initComponets()
{
	_componets.emplace_back(new Map);

	Director::setBuilder(new PlayerTank);

	Director::setBuilderAttributes("Type1", "ColorA", { 64 ,64 });
	_componets.push_back(Director::getResult());
	
	Director::setBuilder(new AiTank);
	
	Director::setBuilderAttributes("Type2", "ColorA", { 64 * 1,64 * 7 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type2", "ColorA", { 64 * 4,64 * 7 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type3", "ColorB", { 64*21,64*19 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type4", "ColorB", { 64 * 40 ,64*3 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type5", "ColorC", {64 * 15,64 * 35});
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type5", "ColorC", { 64 * 28,64 * 6 });
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type6", "ColorD", {64 * 40 ,64 * 6});
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type7", "ColorD", { 64 * 54 ,64 * 34});
	_componets.push_back(Director::getResult());

	Director::setBuilderAttributes("Type8", "ColorD", { 64 *56,64 * 36 });
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
	for (auto& i : _componets)
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