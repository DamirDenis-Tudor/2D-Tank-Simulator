#include "Mediator.h"

map<int, Vector2T<int>> Mediator::_walls = {};
map<const char*, list<int>> Mediator::_teams = {};
map<int, Vector2T<int> > Mediator::_tanks = {};
map<  pair<int, int>, Vector2T<int> > Mediator::_bullets = {};
map< int, int > Mediator::_incomingHits = {};
int Mediator::_currentEnemyId = 0;
map<int, int> Mediator::_pastEnemyId = {};

vector<Vector2T<int>> Mediator::recieveTanksPositions(int tankId)
{

	vector<Vector2T<int>> tanks;

	for (auto& i : _tanks)
	{
		if (i.first != tankId)
		{
			tanks.push_back(i.second);
		}
	}
	return tanks;
}

void Mediator::registerWall(int id , Vector2T<int> pos)
{
	if (_walls.count(id) == 0)
	{
		_walls.insert(pair<int, Vector2T<int>>(id, pos));
		_incomingHits.insert(pair<int, int>(id, 0)); // inregistram un tank cu damage-ul initial primit 0
	}
	else
	{
		_walls[id] = pos;
	}
}

void Mediator::removeWall(int id)
{
	_walls.erase(id);
}

void Mediator::notifyTankPosition(Vector2T<int> pos, int id)
{
	if (_tanks.count(id) == 0)
	{
		_tanks.insert(pair<int, Vector2T<int>>(id, pos));
		_incomingHits.insert(pair<int, int>(id, 0)); // inregistram un tank cu damage-ul initial primit 0
	}
	else
	{
		_tanks[id] = pos;
	}
}
void Mediator::removeTank(int tankId , const char* team)
{
	_tanks.erase(tankId);
	_incomingHits.erase(tankId);
	_teams[team].remove(tankId);
	_pastEnemyId.erase(tankId);
}

bool Mediator::stillExist(int tankId)
{
	if (_tanks.count(tankId))
	{
		return true;
	}
	return false;
}


void Mediator::notifyBulletPosition(Vector2T<int> pos, int tankId, int bulletId)
{
	pair<int, int> idPair = { tankId , bulletId };
	if (_bullets.count(idPair) == 0)
	{
		_bullets.insert(pair<pair<int, int>, Vector2T<int> >(idPair, pos));
	}
	else
	{
		_bullets[idPair] = pos;
	}
}

void Mediator::removeBulletPosition(int tankId, int bulletId)
{
	pair<int, int> pairId = { tankId , bulletId };
	_bullets.erase(pairId);
}

void Mediator::notifyTeam(int tankId, const char* colorTeam)
{
	_teams[colorTeam].push_back(tankId);
}

void Mediator::removeFromTeam(int tankId, const char* colorTeam)
{

	_teams[colorTeam].remove(tankId);
}

Vector2T<int> Mediator::getNearestEnemyPosition(int  id, const char* colorTeam)
{
	float distance = INFINITY;
	for (auto& i : _teams)
	{
		if (i.first != colorTeam)
		{
			for (auto& j : i.second)
			{
				if (Distances::eucliadianDistance(getPosition(id), getPosition(j)) < distance)
				{
					distance = Distances::eucliadianDistance(getPosition(id), getPosition(j));
					_currentEnemyId = j;
				}
			}
		}
	}

	if (!_pastEnemyId.empty() && _currentEnemyId != _pastEnemyId[id])
	{
		if (abs(Distances::eucliadianDistance(getPosition(_currentEnemyId), getPosition(id))
			- Distances::eucliadianDistance(getPosition(_pastEnemyId[id]), getPosition(id))) < 96)
		{
			_currentEnemyId = _pastEnemyId[id];
		}
	}

	_pastEnemyId[id] = _currentEnemyId;

	return getPosition(_currentEnemyId);
}

void Mediator::registerHit(int tankHitted, int damage)
{
	_incomingHits[tankHitted] += damage;
}

int Mediator::checkForDamage(int tankId)
{
	int damage = _incomingHits[tankId];
	_incomingHits[tankId] = 0;

	return damage;
}
