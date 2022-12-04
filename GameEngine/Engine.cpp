#include "Engine.h"

void Engine::initComponets()
{
	_componets.emplace_back(new Map);

	Director* director = new Director;

	PlayerBuilder* builder = new PlayerBuilder();

	builder->setAtributtes("ColorB", "Type5");
	director->setBuilder(builder);

	Tank* tank = director->getTank({ 256 , 1080 }, { 0.4 , 0.4 }, 1);
	_componets.push_back(tank);
	Mediator::setPlayerId(tank->_id);

	EnemyBuilder* builder1 = new EnemyBuilder();
	director->setBuilder(builder1);

	builder1->setAtributtes("ColorC", "Type3");
	Tank* tank1 = director->getTank({ 256 + 128 , 256 + 64 }, { 0.2, 0.2 }, 5);
	_componets.push_back(tank1);

	builder1->setAtributtes("ColorA", "Type1");
	Tank* tank2 = director->getTank({ 256 + 256 + 128 , 256 }, { 0.15 , 0.15 }, 4);
	_componets.push_back(tank2);

	builder1->setAtributtes("ColorD", "Type2");
	Tank* tank3 = director->getTank({ 512 + 256 + 128 , 256 + 64 }, { 0.3 , 0.3 }, 5);
	_componets.push_back(tank3);

	builder1->setAtributtes("ColorB", "Type5");
	Tank* tank4 = director->getTank({ 512 + 256 + 256 ,  256 }, { 0.2 , 0.2 }, 3);
	_componets.emplace_back(tank4);

	_componets.emplace_back(new AnimationsHandler);

	delete director;
	director = nullptr;

	CameraManager::setFocusId(tank->_id);
	tank->cameraIsFollowing();
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
	CameraManager::cameraSync();
	for (auto& i : _componets)
	{
		i->update();
	}
}

Engine::Engine(const char* name, int width, int height, bool fullscreen, float framerate): _framerate(framerate)
{
	InputManager::initInput();
	RendererManager::setRenderer(name, width, height, fullscreen);
	AssetsStorage::loadTiles("levels/level1scaled2.tmx");
	AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");
	AssetsStorage::loadEffects("assets/sTanks/effects.tmx");
	CameraManager::init(AssetsStorage::_mapTileDim, AssetsStorage::_layerWidth, AssetsStorage::_layerHeight);
	initComponets();

}

Engine::~Engine()
{
	RendererManager::clear();
	InputManager::clear();
	AssetsStorage::clear();
	TimeManager::clear();
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