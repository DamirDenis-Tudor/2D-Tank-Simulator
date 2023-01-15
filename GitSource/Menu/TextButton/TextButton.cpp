#include"TextButton.h"

int TextButton::_buttonCount = 0;

TextButton::TextButton(string name , SDL_Color color, int size , int pos , bool hover , int active ) 
	: TextComponent(color, size, name), _name(name) , _isHover(hover) 
{
	_order = _buttonCount;
	int p = _buttonCount;
	_buttonCount = pos;
	setCameraPosition({ RendererManager::_width / 2 - getDimension()._x/2,  _buttonCount * size});
	_buttonCount = p;
	_buttonCount++;

	if (!active)
	{
		disable();
	}
}

TextButton::~TextButton()
{

}

void TextButton::setHoverStatus(bool status)
{
	_isHover = status;
}

void TextButton::setPressedStatus(bool status)
{
	_isPressed = status;
}

int TextButton::getButtonOrder()
{
	return _order;
}

void TextButton::setButtonOrder(int value)
{
	_buttonCount = value;
}

bool TextButton::getHoverStatus()
{
	return _isHover;
}

bool TextButton::getPressedStatus()
{
	return _isPressed;
}

string TextButton::getName()
{
	return _name;
}

void TextButton::update()
{
	if (_isHover && ! _isPressed)
	{
		setColor(GOLD);
	}
	else if(_isPressed)
	{
		setColor(RED);
	}
	else
	{
		setColor(WHITE);
	}
	TextComponent::update();
}