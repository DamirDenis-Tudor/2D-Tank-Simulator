#pragma once

#include"SDL.h"
#include"SDL_image.h"
#include"Vector2i.h"
#include<list>
#include<map>
#include<vector>
#include<iterator>
using namespace std;

/*
	Descrierea clase:
		-> clasa ce ajuta la implementarea design pattern-ului observer
		-> fiecare componenta apeleaza draw, update pentru componenetele sale
		   si acestea la randul lor
		-> identificator de active 
			Ex : 
				Finalizarea unui animatii -> disable => stergerea din vectorul de animatii

		-> are un id -> utiliate : in momentul in care creem un timer vom sti 
								   pentru care componenta este;
*/

class Component
{
protected:
	bool _active = true;

	static int _counter;
public:
	int _id;

	Component()
	{
		_id = _counter;
		_counter++;
	}

	//fiecare clasa care mosteneste va implementa 
	//aceasta medota pentru dealocare
	
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clear() = 0; 

	void enable()
	{
		_active = true;
	}

	void disable()
	{
		_active = false;
	}

	bool isActive()
	{
		return _active;
	}

	void resetCouter()
	{
		_counter = 0;
	}

};

