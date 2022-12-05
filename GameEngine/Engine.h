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
#include"MapSpaceManager.h"

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

	void initComponets();

	void run();

	void draw() override;

	void update() override;

	Engine(const char* name, int width, int height, bool fullscreen, float framerate);
	~Engine();
};