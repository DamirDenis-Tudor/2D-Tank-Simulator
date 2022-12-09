#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	//TODO: 
	// optimizare fiecare inamic va avea raza lui de actiune
	// => verica doar pe portiuni de mapa


	// calculul pozitiilor de mai jos 
	// ajuta la combaterea erorilor cauzate
	// de trunchiere

	//exemplu : mapPos(float) = {1.83 , 3,56} 
	// => (prin trunchiere) mapPos(int) = (1, 3) -> fals

	Vector2T<float> pos;
	pos._x = ((float)Mediator::getPosition(_id)._x / (float)AssetsStorage::_mapTileDim);
	pos._y = ((float)Mediator::getPosition(_id)._y / (float)AssetsStorage::_mapTileDim);

	Vector2T<int> mapPos;

	mapPos._x = (int)pos._x;
	mapPos._y = (int)pos._y;

	if (_moves._left && pos._x - (int)pos._x > 0.1)
	{
		mapPos._x = (int)pos._x + 1;
	}
	if (_moves._up && pos._y - (int)pos._y > 0.1)
	{
		mapPos._y = (int)pos._y + 1;
	}

	Node* start = MapSpaceManager::getNode(mapPos);
	Node* end = MapSpaceManager::getNode(((Mediator::getNearestEnemyPosition(_id, _colorTeam)) / AssetsStorage::_mapTileDim));

	_moves = MapSpaceManager::aStar(start, end, _id);

}

void AiBehavior::BrainAi()
{
	_target = Mediator::getNearestEnemyPosition(_id, _colorTeam) + AssetsStorage::_mapTileDim;
	if (_id != CameraManager::getFocusId())
	{
		_target -= _offset;
	}

	_isActivated = true;

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

	move(position, velocity);
}
