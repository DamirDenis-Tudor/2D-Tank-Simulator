#include "AiBehavior.h"

void AiBehavior::patrol()
{
}

void AiBehavior::follow()
{
	//up down left right shoting
	MapSpaceManager::setUser(_id, _colorTeam);

	_moves = MapSpaceManager::aStar(Mediator::getPosition(_id),	Mediator::getNearestEnemyPosition(_id, _colorTeam) ) ;

	_target = Mediator::getNearestEnemyPosition(_id , _colorTeam) + AssetsStorage::_tileDim;

	//std::cout << Mediator::getNearestEnemyPosition(_id , _colorTeam) <<" "<<_target<<'\n';
}

void AiBehavior::BrainAi()
{
	_isActivated = true;

	if (_isActivated)
	{
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
