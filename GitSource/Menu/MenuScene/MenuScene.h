#pragma once

#include"Component.h"
#include"TextButton.h"
#include"InputManager.h"

/*
	Descriere clasa:
		->un meniu basic

*/
class MenuScene :public Component
{
private:
	string _name;

	string _pressedButtonName = "NONE";
	vector<TextButton*> _buttons;
public:
	MenuScene(string name, vector<TextButton*> _buttons);
	~MenuScene();

	/*
	* functie ce returneaza numele scenei
	*/
	string getName()
	{
		return _name;
	}

	/*
	* functie de returneaza numele butonului apasat
	*/
	string getPressedButtonName()
	{
		return _pressedButtonName;
	}

	int getHoveredButtonOrder()
	{
		for (auto& button : _buttons)
		{
			if (button->getHoverStatus())
			{
				return button->getButtonOrder();
			}
		}
		return 0;
	}


	string getHoveredButtonName()
	{
		for (auto & button : _buttons)
		{
			if (button->getHoverStatus())
			{
				return button->getName();
			}
		}
		return "";
	}
	/*
	* functie ce reseteaza un buton apasat
	*/
	void resetPressedButton();

	/*
	* functie ce seteaza un buton activ sau nu
	*/
	void setButtonStatus(string name, bool status);

	void update() override;
	void draw() override;
};