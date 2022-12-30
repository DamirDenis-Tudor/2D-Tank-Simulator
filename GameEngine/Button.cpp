#include"Button.h"

int Button::_buttonCount = 0;

Button::Button(string name , SDL_Color color, int size) : TextComponent(color, size, name), _type(name)
{
	setCameraPosition({ RendererManager::_width / 2 - getDimension()._x/2, RendererManager::_heigth / 2 - getDimension()._y / 2 + _buttonCount * 64});
	_buttonCount++;
}

Button::~Button()
{

}

void Button::update()
{
	if (_isHover)
	{
		setColor(GOLD);
	}
	else
	{
		setColor(WHITE);
	}
	TextComponent::update();
}