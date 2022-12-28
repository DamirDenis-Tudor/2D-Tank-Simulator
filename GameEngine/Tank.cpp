#include "Tank.h"

Tank::Tank(map<string, SpriteComponent*>& parts, Behavior*& behavior, TankAttributes*& attributes, string type, string color)
	:_parts(parts), _behavior(behavior), _attributes(attributes), _type(type), _teamColor(color)
{
	InfoManager::addInfo( to_string(_id), new TextComponent(RED, 24));

	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getSpawnPosition();
	Mediator::notifyTeam(_id, _teamColor);
	Mediator::registerTank(_position, _id, Health);

	_behavior->setId(_id);
	_behavior->setColorTeam(_teamColor);

	if (CameraManager::getFocusId() == _id)
	{
		cameraIsFollowing();
	}

	//creez timere individuale pe baza unui id-ului
	_respawnTimerId = to_string(_id) + "respawn";
	_launchBulletTimerId = to_string(_id) + "bullet";
	_launchMineTimerId = to_string(_id) + "mine";
	TimeManager::createTimer(_respawnTimerId, rand()%5 + 10);
	TimeManager::createTimer(_launchBulletTimerId, _attributes->_shotingTime);
	TimeManager::createTimer(_launchMineTimerId, 0.2);

}

Tank::~Tank()
{
	for (auto& part : _parts)
	{
		part.second->setSrcTextNullPtr();
		delete part.second;
		part.second = nullptr;
	}
	_parts.clear();

	delete _behavior; _behavior = nullptr;
	delete _attributes; _attributes = nullptr;

	TimeManager::removeTimer(_launchBulletTimerId);
	TimeManager::removeTimer(_launchMineTimerId);
	TimeManager::removeTimer(_respawnTimerId);
	Mediator::removeTank(_id, _teamColor);
}

void Tank::cameraIsFollowing()
{
	for (auto& part : _parts)
	{
		part.second->_isFollowed = true;
	}
}

void Tank::syncMovement()
{
	for (auto& part : _parts)
	{
		part.second->setPosition(_position - CameraManager::offset);
		part.second->update();
	}


	InfoManager::setPosition(to_string(_id),
		Vector2T<int>{ _position._x, _position._y - AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id))._y/2 } +
		AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id)) / 2 - CameraManager::offset);
}

void Tank::launchBullet()
{
	// daca timerul nu este in functiune inseamna ca
		// glotul va fi lansat daca este data "comanda"
	if (!TimeManager::_timers[_launchBulletTimerId]->isTimerWorking() && _behavior->isLaunchingBullet())
	{
		TimeManager::_timers[_launchBulletTimerId]->resetTimer();

		/*
			circumference -> pozitia de inceput a bulletului va fi
			de pe contului cercului format de rotatia cannonului
			-> are acelasi unghi cu al cannon-ului;
		*/
		Vector2T<int> circumference =
		{
			static_cast<int>(SDL_cos((_parts["cannon"]->_angle - 90) * M_PI / 180) * _parts["cannon"]->_dest->w / 2) ,
			static_cast<int>(SDL_sin((_parts["cannon"]->_angle - 90) * M_PI / 180) * _parts["cannon"]->_dest->w / 2)
		};

		SpecialObjectsManager::addBullet(new Bullet(_type, _attributes->_impactAnim, _attributes->_bulletDamage, _position + circumference + _parts["cannon"]->_dest->w / 2, _parts["cannon"]->_angle, _id));
		AnimationsHandler::addAnimation(new AnimationComponent(_attributes->_shotingAnim, _position + circumference + _parts["cannon"]->_dest->w / 2, _parts["cannon"]->_angle));
	}
}

void Tank::launchMine()
{
	// daca timerul nu este in functiune inseamna ca
	// glotul va fi lansat daca este data "comanda"
	if (!TimeManager::_timers[_launchMineTimerId]->isTimerWorking() &&
		_behavior->isLaunchingMine() &&
		SpecialObjectsManager::getMinesNumber(_id) < MaxMinesNumber )
	{
		TimeManager::_timers[_launchMineTimerId]->resetTimer();
		SpecialObjectsManager::addMine(new Mine(_teamColor + "mine" , _position + AssetsStorage::_tileDim, _id));
	}
}

void Tank::checkForHits()
{
	if (Mediator::getHealth(_id) <= 0)
	{
		AnimationsHandler::addAnimation(new AnimationComponent(_teamColor, _position + AssetsStorage::_tileDim, 0));
		temporaryDisable();
	}
	InfoManager::setText(to_string(_id), to_string(Mediator::getHealth(_id)) + "HP");

}

void Tank::temporaryDisable()
{
	for (auto& part : _parts)
	{
		part.second->disable();
	}
	disable();
	TimeManager::_timers[_respawnTimerId]->resetTimer();
	Mediator::removeTank(_id, _teamColor);
	InfoManager::disable(to_string(_id));
	if (_id == CameraManager::getFocusId())
	{
		CameraManager::setSpectatorMode(true);
	}
}

void Tank::respawn()
{
	for (auto& part : _parts)
	{
		part.second->enable();
	}
	enable();
	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getSpawnPosition();
	Mediator::registerTank(_position, _id, Health);
	InfoManager::enable(to_string(_id));

	if (_id == CameraManager::getFocusId())
	{
		CameraManager::setSpectatorMode(false);
	}
}

void Tank::draw()
{
	if (isActive())
	{
		for (auto& part : _parts)
		{
			part.second->draw();
		}
	}
}

void Tank::update()
{
	if (isActive())
	{
		_behavior->movement(_position, _attributes->_velocity);
		_behavior->rotationC(_position, _parts["cannon"]->_angle);
		_behavior->rotationB(_parts["body"]->_angle, _parts["atracks"]->_angle);
		checkForHits();
		launchBullet();
		launchMine();
	}
	else
	{
		if (!TimeManager::_timers[_respawnTimerId]->isTimerWorking())
		{
			respawn();
		}
	}

	syncMovement();
}
