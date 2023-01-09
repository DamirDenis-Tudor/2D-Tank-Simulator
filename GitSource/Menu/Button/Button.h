#pragma once

#include"TextComponent.h"

/*
* Logo-ul ala blana
*/
#define TANC "TAN               "
#define ERMAN    "            ERMAN"
#define LOGO     "++      "
#define LOGO1 "C     "

#define START "Start"
#define EXIT "Exit"

class Button : public TextComponent
{
private:
	string _type;

public:
	static int _buttonCount;
	Button(string name, SDL_Color, int size);
	~Button ();

	bool _isHover = false;
	string getType()
	{
		return _type;
	}

	void update() override;

};