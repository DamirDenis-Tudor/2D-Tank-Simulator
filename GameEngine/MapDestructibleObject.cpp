#include "MapDestructibleObject.h"

MapDestructibleObject::MapDestructibleObject(SpriteComponent* sprite, Vector2T<int> position) :SpriteComponent(sprite), _mapPos(position)
{
	Mediator::registerMapObject(_id, _mapPos , Health);
	TimeManager::createTimer(to_string(_id), rand() % 10 + 20);
	TimeManager::_timers[to_string(_id)]->resetTimer();
	_type = AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x];
}

MapDestructibleObject::~MapDestructibleObject()
{
	Mediator::removeMapObject(_id);
	MapSpaceManager::setObstacles(_mapPos, false);
	TimeManager::removeTimer(to_string(_id));
}

void MapDestructibleObject::temporaryDestroyed()
{
	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = 0;
	Mediator::removeMapObject(_id);
	MapSpaceManager::setObstacles(_mapPos, false);
	disable();
}

void MapDestructibleObject::respawn()
{
	MapSpaceManager::setObstacles(_mapPos, true);
	Mediator::registerMapObject(_id, _mapPos , Health);
	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = _type;
	enable();
}

void MapDestructibleObject::update()
{
	SpriteComponent::update();
	if (!_isBorder)
	{
		if (isActive())
		{
			if (Mediator::getHealth(_id) <= 0)
			{
				temporaryDestroyed();
			}
		}
		else
		{
			MapSpaceManager::setUser(_id);
			if (!TimeManager::_timers[to_string(_id)]->isTimerWorking() && !MapSpaceManager::nodeContainsTemporaryObstacles(MapSpaceManager::getNode(_mapPos)))
			{
				TimeManager::_timers[to_string(_id)]->resetTimer();
				respawn();
			}

		}
	}
}

