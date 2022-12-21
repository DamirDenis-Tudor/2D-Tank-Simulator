#include "InputBehavior.h"

void InputBehavior::syncInput()
{
	_moves._down = InputManager::_down;
	_moves._up = InputManager::_up;
	_moves._left = InputManager::_left;
	_moves._right = InputManager::_right;
	_moves._shoting = InputManager::clicked;
	_moves._releaseMine = InputManager::_m;
	_target = InputManager::mousePos;
	
	// verifica daca posesorul(identifiact dupa id) 
	// este sau nu urmarit de camera
	if (_id == CameraManager::getFocusId())
	{
		_offset = CameraManager::offset;
	}
}

void InputBehavior::movement(Vector2T<int>& position, Vector2T<float> velocity)
{
	syncInput();

	move(position, velocity);
}

