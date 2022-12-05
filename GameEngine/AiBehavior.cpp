#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{

	_moves = { false , false , false, false };

	if (Mediator::getTargetPosition()._x > Mediator::getPosition(_id)._x)
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

	if ( Mediator::getTargetPosition()._x - Mediator::getPosition(_id)._x < 300)
	{
		_moves._right = false;
	}
	if (Mediator::getTargetPosition()._x - Mediator::getPosition(_id)._x > -300)
	{
		_moves._left = false;
	}
	if (Mediator::getTargetPosition()._y - Mediator::getPosition(_id)._y < 300)
	{
		_moves._down = false;
	}
	if (Mediator::getTargetPosition()._y - Mediator::getPosition(_id)._y > -300)
	{
		_moves._up = false;
	}
}

void AiBehavior::BrainAi()
{
	_target = Mediator::getTargetPosition() + AssetsStorage::_mapTileDim;
	if (_id != CameraManager::getFocusId())
	{
		_target -= _offset;
	}

	if (_isActivated)
	{
		follow();
	}
	else
	{
		patrol();
	}
}

void AiBehavior::SyncMoves()
{

}

void AiBehavior::movement(Vector2T<int>& position, Vector2T<float> velocity)
{
	BrainAi();

	SyncMoves();

	_isShooting = true;
	_isActivated = true;

	move(position, velocity);
}
