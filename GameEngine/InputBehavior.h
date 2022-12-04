#pragma once
#include "Behavior.h"
#include "AssetsStorage.h"
#include "CameraManager.h"
#include "InputManager.h"

/*
	Descriere clasa:
		-> 
*/

/*
	TODO:
		->implement syncCamera in Camera Manager
*/

class InputBehavior : public Behavior
{
	void syncInput();

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override;

public:
	InputBehavior()
	{
		//Mediator::setPlayerId(_id);
	}
};

