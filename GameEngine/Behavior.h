#pragma once

#include "Vector2i.h"
#include "ColisionManager.h"
#include"TimeManager.h"
#include"Mediator.h"

/*
	Descriere clasa:

		-> clasa abstracta de descrie compotamentul unui tank:
			> rotatii de doua feluri , miscare 

		Nota: in clasei mostenitoare metoda vrtuala pura movement permite
			  implementarea unui movemnt particular fara a modifica clasa tank
*/

struct Moves
{
	bool _up = false;
	bool _down = false;
	bool _right = false;
	bool _left = false;
};

class Behavior
{
protected:
	int _id = 0;

	Moves _moves;
	bool _isShooting = false;

	//mouse-ul sau un alt tank pentru Ai
	Vector2T<int> _target = { 0 , 0 };

	// daca este PlayerBehavior _offset-ul va fi cel al camerei
	Vector2T<int> _offset = { 0 , 0 };

public:
	virtual void movement(Vector2T<int>& position, Vector2T<float> velocity) = 0;

	void setId(int id)
	{
		_id = id;
	}

	void move(Vector2T<int>& position, Vector2T<float> velocity)
	{
		Vector2T<float> direction(0, 0);

		Vector2T<float> potentialPos;
		//adaug _mapTileDim deoarece vreau punctul de mijloc 
		potentialPos._x = (position._x + AssetsStorage::_mapTileDim);
		potentialPos._y = (position._y + AssetsStorage::_mapTileDim);


		if (_moves._up)
		{
			direction.setY(-1);
			potentialPos._y += 1;
		}
		if (_moves._down)
		{
			direction.setY(1);
		}
		if (_moves._right)
		{
			direction.setX(1);
		}
		if (_moves._left)
		{
			direction.setX(-1);
			potentialPos._x += 1;
		}	//am adaugat 1 la stanga si sus deoarece se realizeaza truchiere

		// normalizam viteza pe diagonala
		if (abs(direction._x) != 0 && abs(direction._y) != 0)
		{
			velocity *= sqrt(velocity._x + velocity._x);
		}

		potentialPos += velocity * direction * TimeManager::getDeltaTime();

		int value = 0;

		int rectDim = 2 * AssetsStorage::_mapTileDim;
		for(auto &i : Mediator::recieveTanksPosition(_id) )
		{
			CollisionManager::circleRectagleCollision(potentialPos, i, rectDim);
		}
		CollisionManager::mapCollision(potentialPos);

		//for ( auto &i : Mediator::recieveTanksPosition(_id))
		//{
		//	std::cout << _id << " : " << i << '\n';
		//}
		//std::cout << "\n\n";

		position._x = static_cast <int>(potentialPos._x) - AssetsStorage::_mapTileDim;
		position._y = static_cast <int>(potentialPos._y) - AssetsStorage::_mapTileDim;
	}

	bool isLaunchingBullet()
	{
		if (_isShooting)
		{
			return true;
		}
		return false;
	}

	void rotationB(float& _angle , float& _angle1)
	{
		/*
		rotatiile au fost strise pe cazuri
		nu este ceva standardizat => au fost testate unele cazuri, dar nu toate
		WARNING : DO NOT TRY THIS AT HOME

	*/
		bool oneKeyPressed = true;
		//directie individuala
		if (_moves._up && !_moves._right && !_moves._left && _angle != 0)
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
		if (_moves._right && !_moves._up && !_moves._down && _angle != 90)
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
		if (_moves._left && !_moves._up && !_moves._down && _angle != -90)
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
		if (_moves._down && !_moves._right && !_moves._left && (_angle != 180 && _angle != -180))
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

		if (_moves._up && _moves._left && _angle != -45 && _angle != 360 - 45)
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
		else if (_moves._up && _moves._right && _angle != 45 && _angle != 45 - 360)
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

		if (_moves._down && _moves._left && _angle != -135 && _angle != 360 - 135)
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
		else if (_moves._down && _moves._right && _angle != 135 && _angle != 135 - 360)
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
			if (_moves._up)
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

		_angle1 = _angle;
	}

	void rotationC(Vector2T<int>& position, float& angle)
	{
		double posY = static_cast<double>(_target._y) + static_cast<double>(_offset._y)
			- (static_cast<double>(position._y) + static_cast<double>(AssetsStorage::_rotCenter->y));

		double posX = static_cast<double>(_target._x) + static_cast<double>(_offset._x)
			- (static_cast<double>(position._x) + static_cast<double>(AssetsStorage::_rotCenter->x));

		angle = (SDL_atan2(posY, posX) * 180 / M_PI) + 90;
	}

};

