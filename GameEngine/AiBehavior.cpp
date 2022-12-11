#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	Vector2T<int> mapPos = { Mediator::getPosition(_id)._x / AssetsStorage::_mapTileDim ,
							Mediator::getPosition(_id)._y / AssetsStorage::_mapTileDim };

	Vector2T<int> mapTarget = (_target - AssetsStorage::_mapTileDim / 2) / AssetsStorage::_mapTileDim;

	Node* start = MapSpaceManager::getNode(mapPos);
	Node* end = MapSpaceManager::getNode(mapTarget);

	_moves = MapSpaceManager::aStar(start, end, _id); 
}

void AiBehavior::BrainAi()
{
	_isActivated = true;

	if (_isActivated)
	{
		_target = Mediator::getNearestEnemyPosition(_id, _colorTeam) + AssetsStorage::_mapTileDim;

		follow();

		if (_id != CameraManager::getFocusId())
		{
			_target -= _offset;
		}

	}
	else
	{
		patrol();
	}
}

void AiBehavior::movement(Vector2T<int>& position, Vector2T<float> velocity)
{

	BrainAi();

	move(position, velocity);
}
