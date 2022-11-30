#pragma once
#include "Behavior.h"
#include "AssetsStorage.h"
#include "CameraManager.h"
#include "InputManager.h"

class InputBehavior : public Behavior
{
	void cameraSync(Vector2T<int>& position)
	{
		CameraManager::pastOffset = CameraManager::offset;

		CameraManager::offset.setX(position.getX() + AssetsStorage::_mapTileDim - RendererManager::_width / 2);
		CameraManager::offset.setY(position.getY() + AssetsStorage::_mapTileDim - RendererManager::_heigth / 2);

		//borders check
		int horizontalBorder = AssetsStorage::_layerWidth * AssetsStorage::_mapTileDim - RendererManager::_width;
		int verticalBorder = AssetsStorage::_layerHeight * AssetsStorage::_mapTileDim - RendererManager::_heigth;
		if (CameraManager::offset.getX() < 0)
		{
			CameraManager::offset.setX(0);
		}
		if (CameraManager::offset.getY() < 0)
		{
			CameraManager::offset.setY(0);
		}
		if (CameraManager::offset.getX() > horizontalBorder)
		{
			CameraManager::offset.setX(horizontalBorder);
		}
		if (CameraManager::offset.getY() > verticalBorder)
		{
			CameraManager::offset.setY(verticalBorder);
		}

		CameraManager::tileOffset = CameraManager::offset - CameraManager::pastOffset;

		_offset = CameraManager::offset;
	}

	void syncInput()
	{
		_down = InputManager::_down;
		_up = InputManager::_up;
		_left = InputManager::_left;
		_right = InputManager::_right;
		_clicked = InputManager::clicked;
		_target = InputManager::mousePos;
	}

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override
	{
		syncInput();

		move(position, velocity);

		cameraSync(position);
	}

	

	
};

