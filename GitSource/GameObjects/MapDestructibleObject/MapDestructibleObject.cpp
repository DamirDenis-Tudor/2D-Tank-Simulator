#include "MapDestructibleObject.h"

MapDestructibleObject::MapDestructibleObject(SpriteComponent* sprite, Vector2T<int> position) :SpriteComponent(sprite), _mapPos(position)
{
	_isSpawnble = true; 

	Mediator::registerMapObject(_id, _mapPos , _health);

	TimeManager::createTimer(to_string(_id), rand() % 10 + 10);

	TimeManager::getTimer(to_string(_id))->resetTimer();

	_name = AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x];
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
	
	Mediator::registerMapObject(_id, _mapPos , _health);

	AssetsStorage::_mapLayers["colidble"][Mediator::getPosition(_id)._y][Mediator::getPosition(_id)._x] = _name;

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
			if (!TimeManager::getTimer(to_string(_id))->isTimerWorking() &&
				!MapSpaceManager::nodeContainsTemporaryObstacles(MapSpaceManager::getNode(_mapPos)))
			{
				/*
				* pentru a putea respawna obiectul pe mapa
				* timerul trebuie sa fie expirat si in locul 
				* nu trebuie sa fie ocupat
				*/
				TimeManager::getTimer(to_string(_id))->resetTimer();
				respawn();
			}

		}
	}
}

