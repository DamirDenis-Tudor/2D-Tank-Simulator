#include "Mediator.h"

int Mediator::_targetId = 0;
map<int, Vector2T<int> > Mediator::_tanks = {};
map<  pair<int, int>, Vector2T<int> > Mediator::_bullets = {};

vector<Vector2T<int>> Mediator::recieveBulletsPosition(int tankId, int bulletId)
{
	vector<Vector2T<int>> enemyBullets;

	pair<int, int> idPair = { tankId , bulletId };
	for (auto& i : _bullets)
	{
		if (idPair.first != i.first.first)
		{
			enemyBullets.push_back(i.second);
		}
	}
	return enemyBullets;
}

vector<Vector2T<int>> Mediator::recieveTanksPosition(int tankId)
{
	vector<Vector2T<int>> enemyTanks;

	for (auto& i : _tanks)
	{
		if (i.first != tankId)
		{
			enemyTanks.push_back(i.second);
		}
	}
	return enemyTanks;
}

void Mediator::notifyTanksPosition(Vector2T<int> pos, int id)
{
	if (_tanks.count(id) == 0) //daca nu a mai fost inregistrat
	{
		_tanks.insert(pair<int, Vector2T<int>>(id, pos));
	}
	else //daca da doar modifcam pozitia
	{
		_tanks[id] = pos;
	}
}

void Mediator::notifyBulletsPosition(Vector2T<int> pos, int tankId, int bulletId)
{
	pair<int, int> idPair = { tankId , bulletId };
	if (_bullets.count(idPair) == 0) //daca nu a mai fost inregistrat
	{
		_bullets.insert(pair<pair<int, int>, Vector2T<int> >(idPair, pos));
	}
	else //daca da doar modifcam pozitia
	{
		_bullets[idPair] = pos;
	}
}

void Mediator::removeBulletsPosition(int tankId, int bulletId)
{
	pair<int, int> pairId = { tankId , bulletId };
	_bullets.erase(pairId);
}

void Mediator::removeTanksPosition(int tankId)
{
	_tanks.erase(tankId);
}
