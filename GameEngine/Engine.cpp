#include "Engine.h"

void Engine::initComponets()
{
	Map* _map = new Map;
	_componets.push_back(_map);

	Director director;
	
	PlayerBuilder* builder = new PlayerBuilder();

	builder->setAtributtes("ColorB", "Type7" );
	director.setBuilder(builder);

	Tank* tank = director.getTank( { 256 , 256 }, { 0.4 , 0.4 }  , 0.2);
	_componets.push_back(tank);

	EnemyBuilder* builder1 = new EnemyBuilder();
	director.setBuilder(builder1);
	
	builder1->setAtributtes("ColorC", "Type6");
	Tank* tank1 = director.getTank( { 256 + 128 , 256 + 64 }, { 0.4 , 0.4 } , 0.5 );
	_componets.push_back(tank1);

	builder1->setAtributtes("ColorA", "Type1");
	Tank* tank2 = director.getTank({ 256 + 256 , 256 + 64 }, { 0.4 , 0.4 } , 0.3);
	_componets.push_back(tank2);

	builder1->setAtributtes("ColorD", "Type2");
	Tank* tank3 = director.getTank({ 512+128 , 256 + 64}, { 0.4 , 0.4 } , 0.6);
	_componets.push_back(tank3);

	builder1->setAtributtes("ColorB", "Type5");
	Tank* tank4 = director.getTank({ 512 + 256 ,  256 + 64 }, { 0.4 , 0.4 } , 0.6);
	_componets.push_back(tank4);

	builder1->setAtributtes("ColorA", "Type4");
	Tank* tank5 = director.getTank({ 512 + 256+128 ,  256 + 64 }, { 0.4 , 0.4 } , 1);
	_componets.push_back(tank5);

	builder1->setAtributtes("ColorD", "Type3");
	Tank* tank6 = director.getTank({ 1024  , 256 + 64 }, { 0.4 , 0.4 } , 1.2);
	_componets.push_back(tank6);

	builder1->setAtributtes("ColorC", "Type8");
	Tank* tank7 = director.getTank({ 1024 + 128 ,  256 + 64 }, { 0.4 , 0.4 } , 1.3);
	_componets.push_back(tank7);

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