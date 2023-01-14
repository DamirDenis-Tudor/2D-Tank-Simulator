#pragma once

#include"SDL.h"
#include"SDL_image.h"
#include"Director.h"
#include"TankBuilder.h"
#include"RendererManager.h"
#include"ColisionManager.h"
#include"Map.h"
#include"TimeManager.h"
#include"InputManager.h"
#include"AnimationsHandler.h"
#include"MapSpaceManager.h"
#include"InfoManager.h"
#include"Menu.h"
#include"SoundManager.h"

/*
	Clasa responsabila pentru :

		-> initializarea/actualizarea managerilor(daca este cazul)
		-> inregistrare event-urilor
		-> mentinerea framerate-ului
*/
class Engine : public Component
{
	float _framerate = 0;
	Component* _menu = nullptr;
	vector<Component*> _components;

public:	

	void initComponets();

	void initGameMap(const char* source);

	void clearGameComponets();

	void initTanks(int teamMembersNumber , string playerType = "NONE", string playerTeam = "NONE");

	void run();

	void draw() override;

	void update() override;

	Engine(const char* name, int width, int height, bool fullscreen, float framerate);
	~Engine();
};