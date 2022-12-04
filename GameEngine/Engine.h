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
	float _framerate = 0;
	vector<Component*> _componets;

public:	
	void run();


	void draw() override;

	void update() override;

	Engine(const char * name , int width ,int height , bool fullscreen , float framerate ) : _framerate(framerate)
	{
		RendererManager::setRenderer(name, width, height, fullscreen);
		InputManager::initInput();

		AssetsStorage::loadTiles("levels/level1scaled2.tmx");
		AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");
		AssetsStorage::loadEffects("assets/sTanks/effects.tmx");

		_componets.emplace_back(new Map);

		Director * director = new Director;

		PlayerBuilder* builder = new PlayerBuilder();

		builder->setAtributtes("ColorB", "Type8");
		director->setBuilder(builder);

		Tank* tank = director->getTank({ 256 , 1080 }, { 0.4 , 0.4 }, 3);
		Mediator::setPlayerId(tank->_id);
		_componets.push_back(tank);

		EnemyBuilder* builder1 = new EnemyBuilder();
		director->setBuilder(builder1);

		builder1->setAtributtes("ColorC", "Type3");
		Tank* tank1 = director->getTank({ 256 + 128 , 256 + 64 }, { 0.2, 0.2 }, 5);
		_componets.push_back(tank1);

		builder1->setAtributtes("ColorA", "Type1");
		Tank* tank2 = director->getTank({ 256 + 256 + 128 , 256 }, { 0.15 , 0.15 }, 0.04);
		_componets.push_back(tank2);

		builder1->setAtributtes("ColorD", "Type2");
		Tank* tank3 = director->getTank({ 512+256 + 128 , 256 + 64}, { 0.3 , 0.3 } , 0.05);
		_componets.push_back(tank3);

		builder1->setAtributtes("ColorB", "Type5");
		Tank* tank4 = director->getTank({ 512 + 256 + 256 ,  256  }, { 0.2 , 0.2 } , 0.05);
		_componets.emplace_back(tank4);

		_componets.emplace_back(new AnimationsHandler);

		delete director;
		director = nullptr;
	}

	~Engine()
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
};