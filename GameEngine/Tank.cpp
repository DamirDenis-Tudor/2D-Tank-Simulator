#include "Tank.h"

Tank::Tank(SpriteComponent* tracks, SpriteComponent* body, SpriteComponent* cannon,
	Behavior* behavior, Vector2T<int> position, Vector2T<float> velocity, float shotingTime, const char* type, const char* color,
	const char* shotingAnim , const char* impactAnim)
	:_tracks(tracks), _body(body), _cannon(cannon), _position(position),
	_behavior(behavior), _velocity(velocity), _shotingTime(shotingTime), _bulletType(type) ,_teamColor(color),
	_shotingAnim(shotingAnim) , _impactAnim(impactAnim)
{
	_spawnPos = _position;
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

	for (auto& i : _bullets)
	{
		delete i;
		i = nullptr;
	}
	_bullets.clear();

	TimeManager::removeTimer(_id);
	Mediator::removeTank(_id , _teamColor);
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

void Tank::checkForBullets()
{
	// daca timerul nu este in functiune inseamna ca
		// glotul va fi lansat daca este data "comanda"
	if (!TimeManager::_timers[_id]->isTimerWorking() && _behavior->isLaunchingBullet())
	{
		TimeManager::_timers[_id]->resetTimer();

		Vector2T<int> circumference =
		{
			static_cast<int>(SDL_cos((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2) ,
			static_cast<int>(SDL_sin((_cannon->_angle - 90) * M_PI / 180) * _cannon->_dest->w / 2)
		};

		/*
			circumference -> pozitia de inceput a bulletului va fi
			de pe contului cercului format de rotatia cannonului
			-> are acelasi unghi cu al cannon-ului;
		*/

		_bullets.emplace_back(new Bullet(_bulletType, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle, _id));
		AnimationsHandler::addAnimation(new Animation(_shotingAnim, _position + circumference + _cannon->_dest->w / 2, _cannon->_angle));
	}
}

void Tank::checkForHits()
{
	health = health - Mediator::checkForDamage(_id);

	if (health <= 0)
	{
		health = 100;
		AnimationsHandler::addAnimation(new Animation(_teamColor, _position + AssetsStorage::_tileDim, 0));
		_position = _spawnPos;
	}
}

void Tank::draw()
{
	_tracks->draw();
	_body->draw();
	_cannon->draw();

	for (auto& i : _bullets)
	{
		i->draw();
	}
}

void Tank::update()
{
	checkForHits();

	_behavior->movement(_position, _velocity);
	_behavior->rotationC(_position, _cannon->_angle);
	_behavior->rotationB(_body->_angle, _tracks->_angle);

	syncMovement();

	checkForBullets();

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->update();

		if (!_bullets[i]->isActive())
		{
			AnimationsHandler::addAnimation(new Animation(_impactAnim, _bullets[i]->_position , _cannon->_angle));
			delete _bullets[i];
			_bullets[i] = nullptr;
			_bullets.erase(_bullets.begin() + i);
			i--;
		}
	}
}
