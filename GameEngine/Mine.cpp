
#include "Mine.h"

Mine::Mine(string type, Vector2T<int> position , int tankId) : _position(position) , _tankId(tankId)
{
	_idle = new Animation(type , position , 0 , 0.05 );
	_idle->setContinuos();
	TimeManager::createTimer(_id , 30);
	TimeManager::_timers[_id]->resetTimer();
}

Mine::~Mine()
{
	delete _idle;
	_idle = nullptr;
	TimeManager::removeTimer(_id);
}

void Mine::draw()
{
	_idle->draw();
}

void Mine::update()
{
	_idle->update();

	bool hasCollision = false;
	int rectDim = 4 * AssetsStorage::_tileDim;
	for (auto& i : Mediator::recieveTanksPositions(_tankId))
	{
		Vector2T<int> rectPos = i - AssetsStorage::_tileDim;
		Vector2T<float> floatPos((float)_position._x, (float)_position._y );
		if (!Mediator::checkTeammates(_tankId, Mediator::getId(i)))
		{
			if (CollisionManager::pointCollisionRectagle(floatPos, rectPos, rectDim))
			{
				hasCollision = true;
				Mediator::registerHit(Mediator::getId(i), 50);
			}
		}
	}

	if (!TimeManager::_timers[_id]->isTimerWorking() || hasCollision)
	{
		disable();
	}
}
