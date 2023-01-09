#include "Tank.h"

Tank::Tank(map<string, SpriteComponent*>& parts, Behavior*& behavior, TankAttributes*& attributes, string type, string color)
	:_parts(parts), _behavior(behavior), _attributes(attributes), _type(type), _teamColor(color)
{
	/*
	* viteza poate fi modificata de abilitatea de SpeedBoost
	*/
	_normalVelocity = _attributes->_velocity;

	/*
	* informatie text depre viata
	*/
	InfoManager::addInfo(to_string(_id ) + "HP", new TextComponent(RED, 24));
	InfoManager::setDrawingBorder(to_string(_id) + "HP");

	/*
	* informatie text despre abilitatea activa
	*/
	InfoManager::addInfo(to_string(_id) + "ability", new TextComponent(GOLD, 20));
	//InfoManager::setDrawingBorder(to_string(_id) + "ability");
	InfoManager::disable(to_string(_id) + "ability");

	/*
	* primeste o pozitie de spawn
	*/
	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getTankSpawnPosition();

	/*
	* il inregistram in mediator
	*/
	Mediator::notifyTeam(_id, _teamColor);
	Mediator::registerTank(_position, _id, Health);

	/*
	* behaviorul trebuie instiintat de posesor
	* (clasa behavior comunica si ea la randul ei cu celelalte obiecte)
	*/
	_behavior->setId(_id);
	_behavior->setColorTeam(_teamColor);

	//creez timere individuale pe baza unui id-ului
	TimeManager::createTimer(to_string(_id) + "respawn", rand() % 5 + 10);
	TimeManager::createTimer(to_string(_id) + "bullet", _attributes->_shotingTime);
	TimeManager::createTimer(to_string(_id) + "mine" , 0.2);
	TimeManager::createTimer(to_string(_id) + "healing", 0.2);

	// timere pentru posibilele abilitati
	TimeManager::createTimer(to_string(_id) + "HealthBoost", 10); // "terminatorul"
	TimeManager::getTimer(to_string(_id) + "HealthBoost")->resetTimer();

	TimeManager::createTimer(to_string(_id) + "ShootingBoost", 10); // "furtuna de gloante"
	TimeManager::getTimer(to_string(_id) + "ShootingBoost")->resetTimer();

	TimeManager::createTimer(to_string(_id) + "SpeedBoost", 10); // "Speedy Gonzalez"
	TimeManager::getTimer(to_string(_id) + "SpeedBoost")->resetTimer();
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

	TimeManager::removeTimer(to_string(_id) + "bullet");
	TimeManager::removeTimer(to_string(_id) + "mine");
	TimeManager::removeTimer(to_string(_id) + "respawn");
	Mediator::removeTank(_id, _teamColor);
}

void Tank::cameraIsFollowing()
{
	for (auto& part : _parts)
	{
		part.second->setCameraFocus(true);
	}
}

void Tank::syncMovement()
{
	for (auto& part : _parts)
	{
		part.second->setCameraPosition(_position - CameraManager::offset);
		part.second->update();
	}
}

void Tank::launchBullet()
{
	bool timerOn = TimeManager::getTimer(to_string(_id) + "bullet")->isTimerWorking();

	InfoManager::disable(to_string(_id) + "reload");
	if (timerOn)
	{
		/*
		* nu se lanseaza glont => afisam textul de reload
		*/

		/*
		* actualizam pozitia textului pentru reload
		*/
		InfoManager::setCameraPosition(to_string(_id) + "reload",
			Vector2T<int>{ _position._x, _position._y - AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id) + "reload")._y / 2 - 40 } +
			AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id) + "reload") / 2 - CameraManager::offset);

		InfoManager::enable(to_string(_id) + "reload");
	}

	if (!timerOn && _behavior->isLaunchingBullet())
	{
		/*
		* se lanseaza glont
		*/

		/*
			resetam timer-ul si dezativam textul de reload
		*/
		TimeManager::getTimer(to_string(_id) + "bullet")->resetTimer();

		/*
			circumference -> pozitia de inceput a bulletului va fi
			de pe contului cercului format de rotatia cannonului
			-> are acelasi unghi cu al cannon-ului;
		*/
		Vector2T<int> circumference =
		{
			static_cast<int>(SDL_cos((_parts["cannon"]->getAngle() - 90) * M_PI / 180) * _parts["cannon"]->getWidth() / 2) ,
			static_cast<int>(SDL_sin((_parts["cannon"]->getAngle() - 90) * M_PI / 180) * _parts["cannon"]->getWidth() / 2)
		};

		SpecialObjectsManager::addBullet(new Bullet(_type, _attributes->_impactAnim, _attributes->_bulletDamage, _position + circumference + _parts["cannon"]->getWidth() / 2, _parts["cannon"]->_angle, _id));
		AnimationsHandler::addAnimation(new AnimationComponent(_attributes->_shotingAnim, _position + circumference + _parts["cannon"]->getWidth() / 2, _parts["cannon"]->getAngle()));
	}
}

void Tank::launchMine()
{
	// daca timerul nu este in functiune inseamna ca
	// mina va fi lansata daca este data "comanda"
	if (!TimeManager::getTimer(to_string(_id) + "mine")->isTimerWorking() &&
		_behavior->isLaunchingMine() &&
		SpecialObjectsManager::getMinesNumber(_id) < MaxMinesNumber)
	{
		TimeManager::getTimer(to_string(_id) + "mine")->resetTimer();
		SpecialObjectsManager::addMine(new Mine(_teamColor + "mine", _position + AssetsStorage::_tileDim, _id));
	}
}

void Tank::checkOfHits()
{
	if (_invincible)
	{
		/*
		* daca este invincibil viata va fi setata la 100
		*/
		Mediator::modifyHealth(_id, 100);
		InfoManager::setText(to_string(_id) + "HP", to_string(Mediator::getHealth(_id)) + "HP");
		return;
	}
	if (Mediator::getHealth(_id) <= 0)
	{
		/*
		* daca este distrus => animatie + disable temporar
		*/
		AnimationsHandler::addAnimation(new AnimationComponent(_teamColor, _position + AssetsStorage::_tileDim, 0));
		temporaryDisable();
	}

	/*
	*  actualizam textul pentru viata
	*/
	InfoManager::setText(to_string(_id) + "HP", to_string(Mediator::getHealth(_id)) + "HP");
}

void Tank::checkOfHealing()
{
	/*
	* actualizam pozitia textului pentru viata
	*/
	InfoManager::setCameraPosition(to_string(_id) + "HP",
		Vector2T<int>{ _position._x, _position._y - AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id) + "HP")._y / 2 } +
		AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id) + "HP") / 2 - CameraManager::offset);

	/*
	* daca este in zona de spawn isi va reface viata
	* in functie de un timer
	*/
	InfoManager::setColor(to_string(_id) + "HP", RED);

	/*
	* pozitia de centru a tank-ului
	*/
	Vector2T<float> floatPos = { (float)_position._x + AssetsStorage::_tileDim , (float)_position._y + AssetsStorage::_tileDim };
	
	/*
	* se verifica daca playerul este in zona de spawn
	*/
	if (!CollisionManager::pointCollisionRectagle(floatPos,
		(Mediator::getSpawnZone(_teamColor) - 1) * AssetsStorage::_tileDim,
		(SpawnRange + 1) * AssetsStorage::_tileDim)) return;

	/*
	*/
	InfoManager::setColor(to_string(_id) + "HP", GREEN);

	if (TimeManager::getTimer(to_string(_id) + "healing")->isTimerWorking()) return;

	Mediator::modifyHealth(_id, 5);
	TimeManager::getTimer(to_string(_id) + "healing")->resetTimer();
}

void Tank::checkOfAbilities()
{
	if (!Mediator::hasActiveAbility(_id)) return;

	string abilityType = Mediator::getAbility(_id);

	if (abilityType == "ShootingBoost")
	{
		TimeManager::getTimer(to_string(_id) + "bullet")->setLimit(_attributes->_shotingTime / 3);
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
		_attributes->_velocity = _normalVelocity * 1.3;
		InfoManager::enable(to_string(_id) + "ability");
		InfoManager::setText(to_string(_id) + "ability", "SPEED");
		InfoManager::enable(to_string(_id) + "abilityTimer");
	}

	/*
	* actualizari pentru textul ce notifica
	* utilizatorul de timpul ramas al abilitatii
	*/
	InfoManager::setText(to_string(_id) + "abilityTimer", "Ability expires in  " + to_string(TimeManager::getTimer(to_string(_id) + abilityType)->getRemainingTime()));

	/*
		setam pozitia pentru timerul de abilitate
	*/
	InfoManager::setCameraPosition(to_string(_id) + "abilityTimer"
		, { RendererManager::_width / 2 - InfoManager::getDimension(to_string(_id) + "abilityTimer")._x / 2
			, 64 });


	/*
		actualizam pozitia ce indica tipul abilitatii active
	*/
	InfoManager::setCameraPosition(to_string(_id) + "ability",
		Vector2T<int>{ _position._x + AssetsStorage::_tileDim - InfoManager::getDimension(to_string(_id) + "ability")._x / 2, _position._y - AssetsStorage::_tileDim + 20 } - CameraManager::offset);

	if (TimeManager::getTimer(to_string(_id) + abilityType)->isTimerWorking()) return;
	
	/*
	* daca timpul a expirat dezactivam animatia
	* si aducem totul la normal
	*/
	Mediator::eraseAbility(_id);

	if (abilityType == "ShootingBoost")
	{
		TimeManager::getTimer(to_string(_id) + "bullet")->setLimit(_attributes->_shotingTime);
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


	/*
	* in scoatem din mediator
	*/
	Mediator::removeTank(_id, _teamColor);
	Mediator::eraseAbility(_id);

	/*
	* resetam timerele
	*/
	TimeManager::getTimer(to_string(_id) + "respawn")->resetTimer();
	TimeManager::getTimer(to_string(_id) + "healing")->resetTimer();
	TimeManager::getTimer(to_string(_id) + "bullet")->resetTimer();
	TimeManager::getTimer(to_string(_id) + "mine")->resetTimer();
	TimeManager::getTimer(to_string(_id) + "HealthBoost")->resetTimer();
	TimeManager::getTimer(to_string(_id) + "ShootingBoost")->resetTimer();
	TimeManager::getTimer(to_string(_id) + "SpeedBoost")->resetTimer();


	// pentru orice eventualitate restabilim caracteriticile initiale
	TimeManager::getTimer(to_string(_id) + "bullet")->setLimit(_attributes->_shotingTime);
	_attributes->_velocity = _normalVelocity;

	/*
	* dezactivam textul
	*/
	InfoManager::disable(to_string(_id) + "ability");
	InfoManager::disable(to_string(_id) + "HP");
	InfoManager::disable(to_string(_id) + "abilityTimer");
	/*
	* daca tank-ul distrus este playerul 
	* => camera = spectator mode
	*/
	if (_id == CameraManager::getFocusId())
	{
		InfoManager::disable(to_string(_id) + "reload");
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

	/*
	* generam pozita de spawn
	*/
	MapSpaceManager::setUser(_id, _teamColor);
	_position = MapSpaceManager::getTankSpawnPosition();

	/*
	* notificam mediatorul
	*/
	Mediator::registerTank(_position, _id, Health);

	/*
	* reactivam textul pentru viata
	*/
	InfoManager::enable(to_string(_id) + "HP");

	/*
	* daca este playerul principal activam camera
	*/
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

		launchBullet();
		launchMine();
		checkOfAbilities();
		checkOfHealing();
		checkOfHits(); 
	}
	else
	{
		/*
		* daca tank-ul principal(al jucatorului) este distrus
		* => text timer pe ecran
		*/
		InfoManager::enable(to_string(_id) + "respawn");

		InfoManager::setText(to_string(_id) + "respawn", "Respawn in " +
			to_string(TimeManager::getTimer(to_string(_id) + "respawn")->getRemainingTime()));

		InfoManager::setCameraPosition(to_string(_id) + "respawn"
			, { RendererManager::_width / 2 - InfoManager::getDimension(to_string(_id) + "respawn")._x / 2
			, RendererManager::_heigth / 2 });

		if (!TimeManager::getTimer(to_string(_id) + "respawn")->isTimerWorking())
		{
			respawn();
			InfoManager::disable(to_string(_id) + "respawn");
		}
	}

	syncMovement();
}
