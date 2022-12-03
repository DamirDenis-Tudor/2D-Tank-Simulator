#include "Engine.h"

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