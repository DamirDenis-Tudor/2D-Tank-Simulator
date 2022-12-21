#include"SpecialObjectsManager.h"

vector<Bullet*> SpecialObjectsManager::_bullets = {};
vector<Mine*> SpecialObjectsManager::_mines = {};


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
}

void SpecialObjectsManager::addBullet(Bullet* bullet)
{
	_bullets.emplace_back(bullet);
}

void SpecialObjectsManager::addMine(Mine* mine)
{
	_mines.emplace_back(mine);
}

void SpecialObjectsManager::update()
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->update();

		if (!_bullets[i]->isActive())
		{
			AnimationsHandler::addAnimation(new Animation(_bullets[i]->_impactAnim, _bullets[i]->_position, _bullets[i]->_angle));
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
			AnimationsHandler::addAnimation(new Animation("BigExplosion", _mines[i]->_position, 0));
			delete _mines[i];
			_mines[i] = nullptr;
			_mines.erase(_mines.begin() + i);
			i--;
		}
	}
}

void SpecialObjectsManager::draw()
{
	for (auto &i : _bullets )
	{
		i->draw();
	}
	for (auto& i : _mines)
	{
		i->draw();
	}
}