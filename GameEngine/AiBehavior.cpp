#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	MapSpaceManager::setUser(_id, _colorTeam);

	_moves = MapSpaceManager::aStar(Mediator::getPosition(_id), Mediator::getNearestEnemyPosition(_id, _colorTeam));

	_target = Mediator::getNearestEnemyPosition(_id, _colorTeam) + AssetsStorage::_tileDim;
}

void AiBehavior::BrainAi()
{
	follow();

	if (_id != CameraManager::getFocusId())
	{
		_target -= _offset;
	}
}

void AiBehavior::movement(Vector2T<int>& position, Vector2T<float> velocity)
{
	if (_isActivated)
	{
		BrainAi();
		move(position, velocity);
	}

}
