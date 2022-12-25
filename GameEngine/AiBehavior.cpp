#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{

	if (Mediator::checkForEnemies(_id , _colorTeam))
	{
		Vector2T<int> target;

		target = Mediator::getNearestEnemyPosition(_id, _colorTeam);
	
		MapSpaceManager::setUser(_id, _colorTeam);
		_moves = MapSpaceManager::aStar(Mediator::getPosition(_id), target);
		
		//pentru depunearea minelor
		if (rand() % 500 == 0)
		{
			_moves._releaseMine = true;
		}

		_target = target + AssetsStorage::_tileDim; // consideram mijlocul
	}
	else
	{
		_moves = { false, false , false , false, false };
	}
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
	//	if (_isActivated)
	{
		BrainAi();
		move(position, velocity);
	}

}
