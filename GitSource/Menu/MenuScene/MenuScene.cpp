#include"MenuScene.h"

/*
* singurul loc unde este o tenta de harcodare
* cauza : criza de timp
*/
bool MenuScene::endGame = false;

MenuScene::MenuScene()
{
	Button::_buttonCount -= 5;
	_title.push_back(new Button(TANC, WHITE, 82));
	Button::_buttonCount -= 1;

	Button* btn= new Button(LOGO, WHITE, 32);
	btn->_isHover = true;
	_title.push_back(btn);

	Button::_buttonCount -= 1;
	
	Button* btn1 = new Button(LOGO1, WHITE, 82);
	btn1->_isHover = true;
	_title.push_back(btn1);

	Button::_buttonCount -= 1;
	_title.push_back(new Button(ERMAN, WHITE, 82));
	Button::_buttonCount += 6;
	
	_start = new Button(START , WHITE , 74);
	_exit = new Button(EXIT, WHITE, 74);

	_start->_isHover = true;
}

MenuScene::~MenuScene()
{
	delete _start;
	delete _exit;

	for (auto &i:_title)
	{
		delete i;
		i = nullptr;
	}
	_title.clear();
}

void MenuScene::update()
{
	if (_start->_isHover && !_exit->_isHover)
	{
		if (InputManager::_enter)
		{
			disable();
		}
		if (InputManager::_down)
		{
			_start->_isHover = false;
			_exit->_isHover = true;
		}
	}
	else if (!_start->_isHover && _exit->_isHover)
	{
		if (InputManager::_enter)
		{
			endGame = true;
		}
		if (InputManager::_up)
		{
			_start->_isHover = true;
			_exit->_isHover = false;
		}
	}

	for (auto& i : _title)
	{
		i->update();
	}
	_start->update();
	_exit->update();
}


void MenuScene::draw()
{
	for (auto& i : _title)
	{
		i->draw();
	}
	_start->draw();
	_exit->draw();
}