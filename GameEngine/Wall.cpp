#include "Wall.h"

Wall::Wall(SpriteComponent* sprite, Vector2T<int> position) :SpriteComponent(sprite), _mapPos(position)
{
	Mediator::registerWall(_id, _mapPos);
	TimeManager::createTimer(_id, 5);
	TimeManager::_timers[_id]->resetTimer();
	_wallType = AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x];
}

Wall::~Wall()
{
	Mediator::removeWall(_id);
	MapSpaceManager::setObstacles(_mapPos, false);
	TimeManager::removeTimer(_id);
}

void Wall::temporaryDestroyed()
{
	_health = 0;
	_isTemporaryDeactivated = true;
	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = 0;
	Mediator::removeWall(_id);
	MapSpaceManager::setObstacles(_mapPos, false);
	disable();
}

void Wall::respawn()
{
	_health = 50;
	_isTemporaryDeactivated = false;
	MapSpaceManager::setObstacles(_mapPos, true);
	Mediator::registerWall(_id, _mapPos);
	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = _wallType;
	enable();
}

void Wall::update()
{
	//creaza un timer pentru fiecare zid pentru a se respwna dupa un anumit timp
	SpriteComponent::update();

	if (!_isBorder)
	{
		if (isActive())
		{
			_health = _health - Mediator::checkForDamage(_id);
			if (_health <= 0)
			{
				temporaryDestroyed();
			}
		}
		else
		{
			MapSpaceManager::setUser(_id);
			if (!TimeManager::_timers[_id]->isTimerWorking() && !MapSpaceManager::nodeContainsTemporaryObstacles(MapSpaceManager::getNode(_mapPos)))
			{
				TimeManager::_timers[_id]->resetTimer();
				respawn();
			}

		}
	}
}

