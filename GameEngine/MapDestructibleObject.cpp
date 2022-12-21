#include "MapDestructibleObject.h"

MapDestructibleObject::MapDestructibleObject(SpriteComponent* sprite, Vector2T<int> position) :SpriteComponent(sprite), _mapPos(position)
{
	Mediator::registerMapObject(_id, _mapPos);
	TimeManager::createTimer(_id, rand()%10 + 10);
	TimeManager::_timers[_id]->resetTimer();
	_type = AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x];
}

MapDestructibleObject::~MapDestructibleObject()
{
	Mediator::removeMapObject(_id);
	MapSpaceManager::setObstacles(_mapPos, false);
	TimeManager::removeTimer(_id);
}

void MapDestructibleObject::temporaryDestroyed()
{
	_health = 0;
	_isTemporaryDeactivated = true;
	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = 0;
	Mediator::removeMapObject(_id);
	MapSpaceManager::setObstacles(_mapPos, false);
	disable();
}

void MapDestructibleObject::respawn()
{
	_health = 50;
	_isTemporaryDeactivated = false;
	MapSpaceManager::setObstacles(_mapPos, true);
	Mediator::registerMapObject(_id, _mapPos);
	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = _type;
	enable();
}

void MapDestructibleObject::update()
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

