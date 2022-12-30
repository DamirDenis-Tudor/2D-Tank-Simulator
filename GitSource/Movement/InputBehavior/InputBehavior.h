#pragma once
#include "Behavior.h"
#include "AssetsStorage.h"
#include "CameraManager.h"
#include "InputManager.h"

/*
	Descriere clasa:
		-> implementeaza movement-ul dictat de comezile externe; 
*/
class InputBehavior : public Behavior
{
	void syncInput();

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override;
};

