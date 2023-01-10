#include"SpecialObjectsManager.h"

vector<Bullet*> SpecialObjectsManager::_bullets = {};
vector<Mine*> SpecialObjectsManager::_mines = {};
vector<AbilityComponent*> SpecialObjectsManager::_abilities = {};


SpecialObjectsManager::SpecialObjectsManager() 
{
}

SpecialObjectsManager::~SpecialObjectsManager()
{
	for (auto &i : _bullets)
	{
		delete i; 
		i = nullptr;
	}
	for (auto& i : _mines)
	{
		delete i;
		i = nullptr;
	}
	for (auto& i : _abilities)
	{
		delete i;
		i = nullptr;
	}
}

void SpecialObjectsManager::addBullet(Bullet* bullet)
{
	_bullets.emplace_back(bullet);
}

void SpecialObjectsManager::addMine(Mine* mine)
{
	_mines.emplace_back(mine);
}

int SpecialObjectsManager::getMinesNumber(int id)
{
	int counter = 0;

	for (auto &mine : _mines )
	{
		if (id == mine->getTankId())
		{
			counter++;
		}
	}
	return counter;
}

void SpecialObjectsManager::spawnAbilities()
{
	if (_abilities.size() >= MaxAbilitiesNumber ) return;

	AbilityComponent* ability = nullptr;
	/*
	* abilitatile sunt spawnate in functie de o probabilitate
	*/
	switch (rand() % 400)
	{
	case ShootingBoost:
		ability = new AbilityComponent("ShootingBoost" , AssetsStorage::_abilities["ShootingBoost"]);
		ability->_position = MapSpaceManager::getObjectSpawnPosition();
		ability->setCameraPosition(ability->_position - CameraManager::offset);
		_abilities.push_back(ability);
		break;

	case HealthBoost:
		ability = new AbilityComponent("HealthBoost" , AssetsStorage::_abilities["HealthBoost"]);
		ability->_position = MapSpaceManager::getObjectSpawnPosition();
		ability->setCameraPosition(ability->_position - CameraManager::offset);
		_abilities.push_back(ability);
		break;

	case SpeedBoost:
		ability = new AbilityComponent("SpeedBoost" , AssetsStorage::_abilities["SpeedBoost"]);
		ability->_position = MapSpaceManager::getObjectSpawnPosition();
		ability->setCameraPosition(ability->_position - CameraManager::offset);
		_abilities.push_back(ability);
		break;
	default:
		break;
	}
}

void SpecialObjectsManager::update()
{
	spawnAbilities();

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->update();

		if (!_bullets[i]->isActive())
		{
			AnimationsHandler::addAnimation(new AnimationComponent(_bullets[i]->_impactAnim, _bullets[i]->_position, _bullets[i]->_angle));
			delete _bullets[i];
			_bullets[i] = nullptr;
			_bullets.erase(_bullets.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < _mines.size(); i++)
	{
		_mines[i]->update();

		if (!_mines[i]->isActive())
		{
			AnimationsHandler::addAnimation(new AnimationComponent(_mines[i]->getType() + "Explosion", _mines[i]->getPosition(), 0, 0.05));
			delete _mines[i];
			_mines[i] = nullptr;
			_mines.erase(_mines.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < _abilities.size(); i++)
	{
		_abilities[i]->update();

		if (!_abilities[i]->isActive())
		{
			//aici poti adauga o animatie
			delete _abilities[i];
			_abilities[i] = nullptr;
			_abilities.erase(_abilities.begin() + i);
			i--;
		}
	}
}

void SpecialObjectsManager::draw()
{
	for (auto & bullet : _bullets )
	{
		bullet->draw();
	}
	for (auto& mine : _mines)
	{
		mine->draw();
	}
	for (auto& ability : _abilities)
	{
		ability->draw();
	}
}