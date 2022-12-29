#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	_moves = { false, false , false , false, false };
	MapSpaceManager::setUser(_id, _colorTeam);

	if (Mediator::getHealth(_id) < 20)
	{
		if (!_isHealing)
		{
			_healingPosition = MapSpaceManager::getTankSpawnPosition();

		}
		_isHealing = true;
	}
	else if(Mediator::getHealth(_id) > 80 )
	{
		_isHealing = false;
	}

	if (Mediator::checkForEnemies(_id, _colorTeam) || _isHealing)
	{
		Vector2T<int> target;
		if (!_isHealing)
		{
			//are un nivel de viata suficient entru a ataca
			target = Mediator::getNearestEnemyPosition(_id, _colorTeam);
		}
		else
		{
			target = _healingPosition;
		}

		// cauta prima mutare
		_moves = MapSpaceManager::aStar(Mediator::getPosition(_id), target , _isHealing);

		//pentru depunearea minelor
		if (rand() % 500 == 0)
		{
			_moves._releaseMine = true;
		}

		if (Mediator::checkForEnemies(_id, _colorTeam))
		{
			// are un _target daca exista cel putin un inamic
			_target = Mediator::getNearestEnemyPosition(_id, _colorTeam) + AssetsStorage::_tileDim;
		}
		else
		{
			// daca nu este clar ca nu va trage
			_moves._shoting = false;
		}
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
