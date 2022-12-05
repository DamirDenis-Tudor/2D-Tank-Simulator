#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	//TODO: 
	// optimizare fiecare inamic va avea raza lui de actiune
	// => verica doar pe portiuni de mapa

	Node* start = MapSpaceManager::getNode((Mediator::getPosition(_id) / AssetsStorage::_mapTileDim));
	Node * end = MapSpaceManager::getNode((Mediator::getTargetPosition() / AssetsStorage::_mapTileDim));

	_moves = MapSpaceManager::aStar(start, end , _id);

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

	//_isShooting = true;
	_isActivated = true;

	move(position, velocity);
}
