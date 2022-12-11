#pragma once

#include"SDL.h"
#include"SDL_image.h"

/*
	Descriere:
		-> creaza un renderer 
		-> permite acesarea acestuia de oriunde
*/
class RendererManager
{
private:
	RendererManager(){}

public:
	static SDL_Renderer* _renderer ;
	static int _width ;
	static int _heigth ;
	
	static void clear()
	{
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}

	static void setRenderer(const char*& name , const int& width, const int& height , bool fullscreen)
	{
		_width = width;
		_heigth = height;

		SDL_Window * window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);
		
		if (window == nullptr)
		{
		//	error("window uninitialized");
		}

		_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (_renderer == nullptr)
		{
			//error("renderer uninitialized");
		}

		SDL_SetRenderDrawColor(_renderer, 120, 10, 50, 3);
	}

	static SDL_Renderer* getRenderer()
	{
		return _renderer;
	}

};

