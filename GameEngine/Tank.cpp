#include "Tank.h"

Tank::Tank(map<string, SpriteComponent*>& parts, Behavior*& behavior, TankAttributes*& attributes, string type, string color)
	:_parts(parts), _behavior(behavior), _attributes(attributes), _type(type), _teamColor(color)
{

	_normalVelocity = _attributes->_velocity;

	InfoManager::addInfo(to_string(_id), new TextComponent(RED, 24));

	InfoManager::addInfo(to_string(_id) + "ability", new TextComponent(GOLD, 20));
	InfoManager::disable(to_string(_id) + "ability");

	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getTankSpawnPosition();
	Mediator::notifyTeam(_id, _teamColor);
	Mediator::registerTank(_position, _id, Health);

	_behavior->setId(_id);
	_behavior->setColorTeam(_teamColor);

	//creez timere individuale pe baza unui id-ului
	_respawnTimerId = to_string(_id) + "respawn";
	TimeManager::createTimer(_respawnTimerId, rand() % 5 + 10);

	_launchBulletTimerId = to_string(_id) + "bullet";
	TimeManager::createTimer(_launchBulletTimerId, _attributes->_shotingTime);

	_launchMineTimerId = to_string(_id) + "mine";
	TimeManager::createTimer(_launchMineTimerId, 0.2);

	_healingTimerId = to_string(_id) + "healing";
	TimeManager::createTimer(_healingTimerId, 0.2);

	// timere pentru posibilele abilitati
	TimeManager::createTimer(to_string(_id) + "HealthBoost", 10); // "terminatorul"
	TimeManager::_timers[to_string(_id) + "HealthBoost"]->resetTimer();

	TimeManager::createTimer(to_string(_id) + "ShootingBoost", 10); // "furtuna de gloante"
	TimeManager::_timers[to_string(_id) + "ShootingBoost"]->resetTimer();

	TimeManager::createTimer(to_string(_id) + "SpeedBoost", 10); // "Speedy Gonzalez"
	TimeManager::_timers[to_string(_id) + "SpeedBoost"]->resetTimer();
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
		part.second->setCameraPosition(_position - CameraManager::offset);
		part.second->update();
	}


	InfoManager::setCameraPosition(to_string(_id),
		Vector2T<int>{ _position._x, _position._y - AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id))._y / 2 } +
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
		SpecialObjectsManager::getMinesNumber(_id) < MaxMinesNumber)
	{
		TimeManager::_timers[_launchMineTimerId]->resetTimer();
		SpecialObjectsManager::addMine(new Mine(_teamColor + "mine", _position + AssetsStorage::_tileDim, _id));
	}
}

void Tank::checkOfHits()
{
	if (_invincible)
	{
		Mediator::modifyHealth(_id, 100);
		InfoManager::setText(to_string(_id), to_string(Mediator::getHealth(_id)) + "HP");
		return;
	}
	if (Mediator::getHealth(_id) <= 0)
	{
		AnimationsHandler::addAnimation(new AnimationComponent(_teamColor, _position + AssetsStorage::_tileDim, 0));
		temporaryDisable();
	}
	InfoManager::setText(to_string(_id), to_string(Mediator::getHealth(_id)) + "HP");
}

void Tank::checkOfHealing()
{
	InfoManager::setColor(to_string(_id), RED);

	Vector2T<float> floatPos = { (float)_position._x + AssetsStorage::_tileDim , (float)_position._y + AssetsStorage::_tileDim };
	if (!CollisionManager::pointCollisionRectagle(floatPos,
		(Mediator::getSpawnZone(_teamColor) - 1) * AssetsStorage::_tileDim,
		(SpawnRange + 1) * AssetsStorage::_tileDim)) return;

	InfoManager::setColor(to_string(_id), GREEN);

	if (TimeManager::_timers[_healingTimerId]->isTimerWorking()) return;

	Mediator::modifyHealth(_id, 4);
	TimeManager::_timers[_healingTimerId]->resetTimer();
}

void Tank::checkOfAbilities()
{
	if (!Mediator::hasActiveAbility(_id)) return;

	string abilityType = Mediator::getAbility(_id);

	if (abilityType == "ShootingBoost")
	{
		TimeManager::_timers[_launchBulletTimerId]->setLimit(_attributes->_shotingTime / 8);
		InfoManager::enable(to_string(_id) + "ability");
		InfoManager::setText(to_string(_id) + "ability", "MACHINE GUN");
		InfoManager::enable(to_string(_id) + "abilityTimer");
	}
	else if (abilityType == "HealthBoost")
	{

		_invincible = true;
		InfoManager::enable(to_string(_id) + "ability");
		InfoManager::setText(to_string(_id) + "ability", "INVINCIBLE");
		InfoManager::enable(to_string(_id) + "abilityTimer");
	}
	else if (abilityType == "SpeedBoost")
	{
		_attributes->_velocity = _normalVelocity * 1.5;
		InfoManager::enable(to_string(_id) + "ability");
		InfoManager::setText(to_string(_id) + "ability", "SPEED");
		InfoManager::enable(to_string(_id) + "abilityTimer");
	}


	InfoManager::setText(to_string(_id) + "abilityTimer", "Ability expires in  " + to_string(TimeManager::_timers[to_string(_id) + abilityType]->getRemainingTime()));

	InfoManager::setCameraPosition(to_string(_id) + "abilityTimer"
		, { RendererManager::_width / 2 - InfoManager::getDimension(to_string(_id) + "abilityTimer")._x / 2
			, 64 });

	InfoManager::setCameraPosition(to_string(_id) + "ability",
		Vector2T<int>{ _position._x + AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id) + "ability")._x / 2, _position._y - AssetsStorage::_tileDim + 20 } - CameraManager::offset);

	if (TimeManager::_timers[to_string(_id) + abilityType]->isTimerWorking()) return;

	Mediator::eraseAbility(_id);

	if (abilityType == "ShootingBoost")
	{
		TimeManager::_timers[_launchBulletTimerId]->setLimit(_attributes->_shotingTime);
	}
	else if (abilityType == "HealthBoost")
	{
		_invincible = false;
	}
	else if (abilityType == "SpeedBoost")
	{
		_attributes->_velocity = _normalVelocity;
	}

	InfoManager::disable(to_string(_id) + "ability");
	InfoManager::disable(to_string(_id) + "abilityTimer");
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
	Mediator::eraseAbility(_id);

	InfoManager::disable(to_string(_id) + "ability");
	InfoManager::disable(to_string(_id));

	TimeManager::_timers[to_string(_id) + "HealthBoost"]->resetTimer();
	TimeManager::_timers[to_string(_id) + "ShootingBoost"]->resetTimer();
	TimeManager::_timers[to_string(_id) + "SpeedBoost"]->resetTimer();

	InfoManager::disable(to_string(_id) + "abilityTimer");

	// pentru oric eventualitate restabilim caraccteriticile initiale
	TimeManager::_timers[_launchBulletTimerId]->setLimit(_attributes->_shotingTime);
	_attributes->_velocity = _normalVelocity;

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
	_position = MapSpaceManager::getTankSpawnPosition();
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
		checkOfHits();
		checkOfHealing();
		checkOfAbilities();
		launchBullet();
		launchMine();
	}
	else
	{
		InfoManager::enable(to_string(_id) + "respawn");
		InfoManager::setText(to_string(_id) + "respawn", "Respawn in " + to_string(TimeManager::_timers[_respawnTimerId]->getRemainingTime()));
		InfoManager::setCameraPosition(to_string(_id) + "respawn"
			, { RendererManager::_width / 2 - InfoManager::getDimension(to_string(_id) + "respawn")._x / 2
			, RendererManager::_heigth / 2 });
		if (!TimeManager::_timers[_respawnTimerId]->isTimerWorking())
		{
			respawn();
			InfoManager::disable(to_string(_id) + "respawn");
		}
	}

	syncMovement();
}
