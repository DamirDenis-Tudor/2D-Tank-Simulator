#pragma once
#include "Behavior.h"
#include<queue>


/*
	Descriere clasa:

		->
*/

/*
	todo:
		-> implementare A*
		-> implementarea unei cozi cu miscari optimale pe baza algoritmului
		   ex: _down , _left , _left , _left
*/

class AiBehavior : public Behavior
{
	//queue<Moves> _movingOrder;
	bool _isActivated = false;

public:

	void patrol()
	{
	}

	void follow()
	{
		_moves = { false , false , false, false };

		if (Mediator::getTargetPosition()._x > Mediator::getPosition(_id)._x )
		{
			_moves._right = true;
		}
		else if (Mediator::getTargetPosition()._x < Mediator::getPosition(_id)._x)
		{
			_moves._left = true;
		}

		if (Mediator::getTargetPosition()._y > Mediator::getPosition(_id)._y)
		{
			_moves._down = true;
		}
		else if (Mediator::getTargetPosition()._y < Mediator::getPosition(_id)._y)
		{
			_moves._up = true;
		}
		//std::cout<< Mediator::getTargetPosition()._x - Mediator::getPosition(_id)._x <<"\n";

		/*if ( Mediator::getTargetPosition()._x - Mediator::getPosition(_id)._x < 500)
		{
			_moves._right = false;
		}
		if (Mediator::getTargetPosition()._x - Mediator::getPosition(_id)._x > -500)
		{
			_moves._left = false;
		}
		if (Mediator::getTargetPosition()._y - Mediator::getPosition(_id)._y < 500)
		{
			_moves._down = false;
		}
		if (Mediator::getTargetPosition()._y - Mediator::getPosition(_id)._y > -500)
		{
			_moves._up = false;
		}*/
	}

	void BrainAi()
	{
		_target = Mediator::getTargetPosition() + AssetsStorage::_mapTileDim;

		if (_isActivated)
		{
			follow();
		}
		else
		{
			patrol();
		}
	}

	void SyncMoves()
	{

	}

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override
	{
		BrainAi();

		SyncMoves();

		_isShooting = true;
		_isActivated = true;

		move(position, velocity);
	}

};

