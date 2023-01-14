#include"MenuScene.h"
#include"SoundManager.h"

MenuScene::MenuScene(string name, vector<TextButton*> buttons) : _name(name), _buttons(buttons)
{
	/*
	* creeam timer-ull pentru a putea naviga pe butoane
	*/
	TimeManager::createTimer(to_string(_id), 1);

	TimeManager::getTimer(to_string(_id))->resetTimer();

	TextButton::setButtonOrder(0);

	if (name == "Main") return;

	disable();

	TextButton::resetOrder();
}

MenuScene::~MenuScene()
{
	for (auto& button : _buttons)
	{
		delete button;
		button = nullptr;
	}
}

void MenuScene::resetPressedButton()
{
	for (auto& button : _buttons)
	{
		if (button->getName() != _pressedButtonName) continue;

		button->setPressedStatus(false);
		_pressedButtonName = "NONE";
	}
}

void MenuScene::setButtonStatus(string name, bool status)
{
	for (auto& button : _buttons)
	{
		if (button->getName() != name) continue;

		status ? button->enable() : button->disable();
	}
}

void MenuScene::update()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->update();

		/*
		* daca button-ul nu este activ 
		*/
		if (!_buttons[i]->isActive()) continue;

		/*
		* daca timer inca merge
		*/
		if (TimeManager::getTimer(to_string(_id))->isTimerWorking()) continue;

		/*
		*	daca timer-ul nu mai merge
		*	si este apasat de la tastatura _down(S) si 
			butonul este hover(si nu este ultimul buton)
		*/
		if( InputManager::_down && _buttons[i]->getHoverStatus() && i != _buttons.size() - 1)
		{
			/*
			* resetam timer-ul
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();
			
			/*
			*	dezactivam hover-ul 
			*/
			_buttons[i]->setHoverStatus(false);
			
			/*
			* activam hover-ul pentru butonul urmator
			*/
			_buttons[i + 1]->setHoverStatus(true);

			SoundManager::playSoundEfect("switch");
		}
		/*
		*/
		else if(InputManager::_up && _buttons[i]->getHoverStatus() && i != 0 && _buttons[i-1]->isActive())
		{
			/*
			* resetam timer-ul
			*/
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			*	dezactivam hover-ul
			*/
			_buttons[i]->setHoverStatus(false);

			/*
			* activam hover-ul pentru butonul precedent
			*/
			_buttons[i - 1]->setHoverStatus(true);

			SoundManager::playSoundEfect("switch");
		}
		else if(InputManager::_enter && _buttons[i]->getHoverStatus())
		{
			TimeManager::getTimer(to_string(_id))->resetTimer();

			/*
			* setam butonul apasat si retinem numele lui
			*/
			_buttons[i]->setPressedStatus(true);

			_pressedButtonName = _buttons[i]->getName();

			SoundManager::playSoundEfect("click");
		}
	}
}


void MenuScene::draw()
{
	for (auto& button : _buttons)
	{
		button->draw();
	}
}