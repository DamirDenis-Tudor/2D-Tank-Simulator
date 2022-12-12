#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	Vector2T<float> pos = { (float)Mediator::getPosition(_id)._x / (float)AssetsStorage::_tileDim ,
							(float)Mediator::getPosition(_id)._y / (float)AssetsStorage::_tileDim };

	Vector2T<int> mapTarget = (_target - AssetsStorage::_tileDim ) / AssetsStorage::_tileDim;

	//if (_moves._up && pos._x - (int)pos._x > 0)
	//{
	//	pos._x += 1;
	//}


	Vector2T<int>mapPos = { (int)pos._x , (int)pos._y };

	Node* start = MapSpaceManager::getNode(mapPos);
	Node* end = MapSpaceManager::getNode(mapTarget);

	_moves = MapSpaceManager::aStar(start, end, _id); 
}

void AiBehavior::BrainAi()
{
	_isActivated = true;

	if (_isActivated)
	{
		_target = Mediator::getNearestEnemyPosition(_id, _colorTeam) + AssetsStorage::_tileDim;

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
