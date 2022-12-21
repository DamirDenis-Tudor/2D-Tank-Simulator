#include "Tank.h"

Tank::Tank(SpriteComponent* tracks, SpriteComponent* body, SpriteComponent* cannon,
	Behavior* behavior, Vector2T<float> velocity, float shotingTime, int bulletDamage, const char* type, const char* color,
	const char* shotingAnim, const char* impactAnim)
	:_tracks(tracks), _body(body), _cannon(cannon),
	_behavior(behavior), _velocity(velocity), _shotingTime(shotingTime), _bulletDamage(bulletDamage), _bulletType(type), _teamColor(color),
	_shotingAnim(shotingAnim), _impactAnim(impactAnim)
{
	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getSpawnPosition();

	TimeManager::createTimer(_id, _shotingTime);

	Mediator::notifyTeam(_id, _teamColor);
	Mediator::notifyTankPosition(_position, _id);

	_behavior->setId(_id);
	_behavior->setColorTeam(_teamColor);

	if (CameraManager::getFocusId() == _id)
	{
		cameraIsFollowing();
	}
}

Tank::~Tank()
{
	_tracks->setSrcTextNullPtr();
	delete _tracks; _tracks = nullptr;

	_body->setSrcTextNullPtr();
	delete _body; _body = nullptr;

	_cannon->setSrcTextNullPtr();
	delete _cannon; _cannon = nullptr;

	delete _behavior; _behavior = nullptr;

	TimeManager::removeTimer(_id);
	Mediator::removeTank(_id, _teamColor);
}

void Tank::cameraIsFollowing()
{
	_tracks->_isFollowed = true;
	_body->_isFollowed = true;
	_cannon->_isFollowed = true;
}

void Tank::syncMovement()
{
	_tracks->setPosition(_position - CameraManager::offset);
	_body->setPosition(_position - CameraManager::offset);
	_cannon->setPosition(_position - CameraManager::offset);

	_tracks->update();
	_body->update();
	_cannon->update();
}

void Tank::launchBullet()
{
	// daca timerul nu este in functiune inseamna ca
		// glotul va fi lansat daca este data "comanda"
	if (!TimeManager::_timers[_id]->isTimerWorking() && _behavior->isLaunchingBullet())
	{
		TimeManager::_timers[_id]->resetTimer();

		/*
			circumference -> pozitia de inceput a bulletului va fi
			de pe contului cercului format de rotatia cannonului
			-> are acelasi unghi cu al cannon-ului;
		*/
		Vector2T<int> circumference =
		{
			static_cast<int>(SDL_cos((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2) ,
			static_cast<int>(SDL_sin((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2)
		};

		SpecialObjectsManager::addBullet(new Bullet(_bulletType, _impactAnim , _bulletDamage, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle, _id));
		AnimationsHandler::addAnimation(new Animation(_shotingAnim, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle));
	}
}

void Tank::launchMine()
{
	// daca timerul nu este in functiune inseamna ca
	// glotul va fi lansat daca este data "comanda"
	if (!TimeManager::_timers[_id]->isTimerWorking() && _behavior->isLaunchingMine())
	{
		TimeManager::_timers[_id]->resetTimer();
		SpecialObjectsManager::addMine(new Mine("mineA" , _position + AssetsStorage::_tileDim , _id) );
	}
}

void Tank::checkForHits()
{
	health = health - Mediator::checkForDamage(_id);

	if (health <= 0)
	{
		AnimationsHandler::addAnimation(new Animation(_teamColor, _position + AssetsStorage::_tileDim, 0));
		temporaryDisable();
	}
}

void Tank::temporaryDisable()
{
	_tracks->_isTemporaryDeactivated = true;
	_body->_isTemporaryDeactivated = true;
	_cannon->_isTemporaryDeactivated = true;
	disable();
	health = 0;
	TimeManager::modifyTimer(_id, 10);
	TimeManager::_timers[_id]->resetTimer();
	Mediator::removeTank(_id, _teamColor);
}

void Tank::respawn()
{
	TimeManager::modifyTimer(_id, _shotingTime);
	_tracks->_isTemporaryDeactivated = false;
	_body->_isTemporaryDeactivated = false;
	_cannon->_isTemporaryDeactivated = false;
	enable();
	health = 100;
	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getSpawnPosition();
	Mediator::notifyTankPosition(_position, _id);
	Mediator::notifyTeam(_id, _teamColor);
}

void Tank::draw()
{
	if (isActive())
	{
		_tracks->draw();
		_body->draw();
		_cannon->draw();
	}
}

void Tank::update()
{
	if (isActive())
	{
		_behavior->movement(_position, _velocity);
		_behavior->rotationC(_position, _cannon->_angle);
		_behavior->rotationB(_body->_angle, _tracks->_angle);
		checkForHits();
		launchBullet();
		launchMine();
	}
	else
	{
		if (!TimeManager::_timers[_id]->isTimerWorking())
		{
			respawn();
		}
	}

	syncMovement();
}
