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
	void cameraSync(Vector2T<int>& position);

	void syncInput();

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override;
	
};

