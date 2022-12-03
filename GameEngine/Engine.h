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
	static Map* memoryleak;
	vector<Component*> _componets;
	float _framerate = 0;

public:
	void initComponets();
	void run();

	void draw() override
	{
		for (auto& i : _componets)
		{
			i->draw();
		}
	}

	void update() override
	{
		for (auto& i : _componets)
		{
			i->update();
		}
	}

	Engine(const char * name , int width ,int height , bool fullscreen , float framerate ) : _framerate(framerate)
	{
		RendererManager::setRenderer(name, width, height, fullscreen);
		InputManager::initInput();
		AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");
		AssetsStorage::loadTiles("levels/level1scaled2.tmx");
		AssetsStorage::loadEffects("assets/sTanks/effects.tmx");

		initComponets();
	}

	void clear() override
	{
		for (int i = 0; i < _componets.size(); i++)
		{
			_componets[i]->clear();
			_componets[i] = 0;
		}
		_componets.clear();

		InputManager::clear();
		AssetsStorage::clear();
		TimeManager::clear();
	}


};