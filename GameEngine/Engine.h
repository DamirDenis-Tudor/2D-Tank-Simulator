#pragma once

#include "SDL.h"
#include"SDL_image.h"

#include"Tank.h"
#include"Director.h"
#include"PlayerBuilder.h"
#include"EnemyBuilder.h"
#include"AssetsStorage.h"
#include"RendererManager.h"
#include"ColisionManager.h"
#include"Map.h"
#include"TimeManager.h"
#include"InputManager.h"
#include"AnimationsHandler.h"

/*
	Clasa responsabila pentru :

		-> initializarea managerilor(daca este cazul)
		-> gameloop
		-> apelul funtiilor de draw , update pentru celelalte componente
*/

class Engine : public Component
{
	Map* _map = nullptr;
	vector<Tank*> _tanks;
	AnimationsHandler* _animHndl;
	float _framerate = 0;

public:
	void initComponets();
	void run();

	void draw() override
	{
		_map->draw();
		for (auto& i : _tanks)
		{
			i->draw();
		}
		_animHndl->draw();
	}

	void update() override
	{
		_map->update();
		for (auto& i : _tanks)
		{
			i->update();
		}
		_animHndl->update();
	}

	Engine(const char * name , int width ,int height , bool fullscreen , float framerate ) : _framerate(framerate)
	{
		RendererManager::setRenderer(name, width, height, fullscreen);
		InputManager::initInput();

		AssetsStorage::loadTiles("levels/level1scaled2.tmx");
		AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");
		AssetsStorage::loadEffects("assets/sTanks/effects.tmx");

		_map = new Map;

		Director * director = new Director;

		PlayerBuilder* builder = new PlayerBuilder();

		builder->setAtributtes("ColorB", "Type5");
		director->setBuilder(builder);

		Tank* tank = director->getTank({ 256 , 1080 }, { 0.3 , 0.3 }, 0.6);
		Mediator::setPlayerId(tank->_id);
		_tanks.push_back(tank);

		EnemyBuilder* builder1 = new EnemyBuilder();
		director->setBuilder(builder1);

		builder1->setAtributtes("ColorC", "Type6");
		Tank* tank1 = director->getTank({ 256 + 128 , 256 + 64 }, { 0.1 , 0.1 }, 3.5);
		_tanks.push_back(tank1);

		builder1->setAtributtes("ColorA", "Type1");
		Tank* tank2 = director->getTank({ 256 + 256 + 128 , 256 }, { 0.1 , 0.1 }, 3);
		_tanks.push_back(tank2);

		builder1->setAtributtes("ColorD", "Type2");
		Tank* tank3 = director->getTank({ 512+256 + 128 , 256 + 64}, { 0.1 , 0.1 } , 2);
		_tanks.push_back(tank3);

		builder1->setAtributtes("ColorB", "Type5");
		Tank* tank4 = director->getTank({ 512 + 256 + 256 ,  256  }, { 0.1 , 0.1 } , 2);
		_tanks.emplace_back(tank4);

		_animHndl = new AnimationsHandler;

		delete director;
		director = nullptr;
	}

	~Engine()
	{

		RendererManager::clear();
		InputManager::clear();
		AssetsStorage::clear();
		TimeManager::clear();
		
		delete _map;
		_map = nullptr;
		for (auto& i : _tanks)
		{
			delete i;
			i = nullptr;
		}
		_tanks.clear();

		delete _animHndl;
		_animHndl = nullptr;

	}
};