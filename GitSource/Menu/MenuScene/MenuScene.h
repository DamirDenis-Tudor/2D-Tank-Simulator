#pragma once

#include"Component.h"
#include"Button.h"
#include"InputManager.h"

/*
	Descriere clasa:
		->un meniu basic

*/
class MenuScene :public Component
{
private:
	vector<Component*> _title;

	Button* _start;
	Button* _exit;
public:
	static bool endGame;
	MenuScene();
	~MenuScene();

	void update() override;
	void draw() override;
};