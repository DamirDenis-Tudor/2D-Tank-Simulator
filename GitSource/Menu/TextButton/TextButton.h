#pragma once

#include"TextComponent.h"

class TextButton : public TextComponent
{
private:
	static int _buttonCount;

	string _name;
	bool _isHover = false;
	bool _isPressed = false;
	bool _used= true;
	int _order;

public:
	TextButton(string name, SDL_Color, int size, int pos, bool hover = false,  int active = true);

	~TextButton();

	void setHoverStatus(bool status);

	void setPressedStatus(bool status);

	int getButtonOrder();

	static void setButtonOrder(int value);

	bool getHoverStatus();

	bool getPressedStatus();

	string getName();

	static void resetOrder()
	{
		_buttonCount = 0;
	}

	void update() override;
};