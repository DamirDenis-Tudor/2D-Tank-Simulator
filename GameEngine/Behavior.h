#pragma once

#include "Vector2i.h"
#include "ColisionManager.h"
#include"TimeManager.h"

class Behavior
{
protected:
	bool _up = false;
	bool _down = false;
	bool _right = false;
	bool _left = false;
	bool _clicked = false;
	Vector2T<int> _target = { 0 , 0 };

public:
	virtual void movement(Vector2T<int>& position, Vector2T<float> velocity) = 0;
	virtual void rotationC(Vector2T<int>& position, float& angle) = 0;

	void move(Vector2T<int>& position, Vector2T<float> velocity)
	{
		Vector2T<float> direction(0, 0);

		Vector2T<float> potentialPos;
		potentialPos._x = (position._x + AssetsStorage::_mapTileDim);
		potentialPos._y = (position._y + AssetsStorage::_mapTileDim);


		if (_up)
		{
			direction.setY(-1);
			potentialPos._y += 1;
		}
		if (_down)
		{
			direction.setY(1);
		}
		if (_right)
		{
			direction.setX(1);
		}
		if (_left)
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


		CollisionManager::circleCollision(potentialPos);

		position._x = static_cast <int>(potentialPos._x) - AssetsStorage::_mapTileDim;
		position._y = static_cast <int>(potentialPos._y) - AssetsStorage::_mapTileDim;
	}


	bool isLaunchingBullet()
	{
		if (_clicked)
		{
			return true;
		}
		return false;
	}

	void rotationB(float& _angle)
	{
		/*
		rotatiile au fost strise pe cazuri
		nu este ceva standardizat => au fost testate unele cazuri, dar nu toate
		WARNING : DO NOT TRY THIS AT HOME

	*/
		bool oneKeyPressed = true;
		//directie individuala
		if (_up && !_right && !_left && _angle != 0)
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
		if (_right && !_up && !_down && _angle != 90)
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
		if (_left && !_up && !_down && _angle != -90)
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
		if (_down && !_right && !_left && (_angle != 180 && _angle != -180))
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

		if (_up && _left && _angle != -45 && _angle != 360 - 45)
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
		else if (_up && _right && _angle != 45 && _angle != 45 - 360)
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

		if (_down && _left && _angle != -135 && _angle != 360 - 135)
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
		else if (_down && _right && _angle != 135 && _angle != 135 - 360)
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
			if (_up)
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

