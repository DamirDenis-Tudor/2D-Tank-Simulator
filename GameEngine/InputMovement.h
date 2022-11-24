#pragma once
#include "Movement.h"
#include "AssetsStorage.h"
#include "CameraManager.h"
#include "RendererManager.h"
#include"TimeManager.h"

class InputMovement : public Movement
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
	}

	void move(Vector2T<int>& position, Vector2T<float> velocity) override
	{

		Vector2T<float> direction(0, 0);

		Vector2T<float> potentialPos;
		potentialPos._x = (position._x + AssetsStorage::_mapTileDim);
		potentialPos._y = (position._y + AssetsStorage::_mapTileDim);


		if (InputManager::_up)
		{
			direction.setY(-1);
			potentialPos._y += 1;
		}
		if (InputManager::_down)
		{
			direction.setY(1);
		}
		if (InputManager::_right)
		{
			direction.setX(1);
		}
		if (InputManager::_left)
		{
			direction.setX(-1);
			potentialPos._x += 1;
		}

		//normalazi velocity vector when moove diagonally
		if (abs(direction._x) != 0 && abs(direction._y) != 0)
		{
			velocity *= sqrt(velocity._x + velocity._x);

		}

		potentialPos += velocity * direction * TimeManager::getDeltaTime();


		CollisionManager::mapCollision(potentialPos);

		position._x = static_cast <int>(potentialPos._x) - AssetsStorage::_mapTileDim;
		position._y = static_cast <int>(potentialPos._y) - AssetsStorage::_mapTileDim;

		cameraSync(position);
	}

	void rotationC(Vector2T<int>& position, float& angle) override
	{
		if (InputManager::mousePos.getX() != 0 && InputManager::mousePos.getY() != 0)
		{
			angle = (int)(SDL_atan2(static_cast<double>(InputManager::mousePos.getY() + CameraManager::offset.getY() - (position.getY() + AssetsStorage::_rotCenter->y)),
				static_cast<double>(InputManager::mousePos.getX() + CameraManager::offset.getX() - (position.getX() + AssetsStorage::_rotCenter->x))) * 180 / M_PI) + 90;
		}
	}
	void rotationB(float& _angle) override
	{
		/*
		rotatiile au fost strise pe cazuri
		nu este ceva standardizat => au fost testate unele cazuri, dar nu toate
		WARNING : DO NOT TRY THIS AT HOME

	*/
		bool oneKeyPressed = true;
		//directie individuala
		if (InputManager::_up && !InputManager::_right && !InputManager::_left && _angle != 0)
		{

			if ((_angle >= 0 && _angle <= 180) || _angle < -180)
			{
				_angle -= 5;
			}
			else if ((_angle <= 0 && _angle >= -180) || _angle > 180)
			{
				_angle += 5;
			}

		}
		if (InputManager::_right && !InputManager::_up && !InputManager::_down && _angle != 90)
		{
			if (_angle <= -180 || (_angle <= 180 && _angle >= 90) || _angle <= -90)
			{
				_angle -= 5;
			}
			else if (_angle >= 0 || (_angle > -90))
			{
				_angle += 5;
			}
		}
		if (InputManager::_left && !InputManager::_up && !InputManager::_down && _angle != -90)
		{
			if (_angle >= 180 || (_angle >= -180 && _angle <= -90) || _angle >= 90)
			{
				_angle += 5;
			}
			else if (_angle <= 0 || (_angle < 90))
			{
				_angle -= 5;
			}
		}
		if (InputManager::_down && !InputManager::_right && !InputManager::_left && (_angle != 180 && _angle != -180))
		{
			if (_angle >= 90 || (_angle >= 0 && _angle < 90))
			{
				_angle += 5;
			}
			else if (_angle <= 0)
			{
				_angle -= 5;
			}
		}

		//directie comuna

		if (InputManager::_up && InputManager::_left && _angle != -45 && _angle != 360 - 45)
		{
			oneKeyPressed = false;
			if ((_angle >= 180 && _angle >= 45) || (_angle <= 0 && _angle <= -45))
			{
				_angle += 5;
			}
			else
			{
				_angle -= 5;
			}

		}
		else if (InputManager::_up && InputManager::_right && _angle != 45 && _angle != 45 - 360)
		{
			oneKeyPressed = false;
			if (_angle > -180 && _angle > 180 || (_angle >= 0 && _angle <= 45))
			{
				_angle += 5;
			}
			else
			{
				_angle -= 5;
			}

		}

		if (InputManager::_down && InputManager::_left && _angle != -135 && _angle != 360 - 135)
		{
			oneKeyPressed = false;
			if (_angle <= 0 && _angle >= -135)
			{
				_angle -= 5;
			}
			else
			{
				_angle += 5;
			}
		}
		else if (InputManager::_down && InputManager::_right && _angle != 135 && _angle != 135 - 360)
		{
			if (_angle >= 0 && _angle <= 135)
			{
				_angle += 5;
			}
			else
			{
				_angle -= 5;
			}
		}

		//translari
		if (oneKeyPressed)
		{
			if (_angle == -270)
			{
				_angle = 90;
			}
			if (_angle == 270)
			{
				_angle = -90;
			}
		}

		if (_angle == 360 - 45)
		{
			_angle = -45;
		}

		if (!oneKeyPressed)
		{
			if (InputManager::_up)
			{
				if (_angle == 45 - 360)
				{
					_angle = 45;
				}
				if (_angle == -45)
				{
					_angle = 360 - 45;
				}
			}
		}


		if (_angle >= 360 || _angle <= -360)
		{
			_angle = 0;
		}

	}
};

