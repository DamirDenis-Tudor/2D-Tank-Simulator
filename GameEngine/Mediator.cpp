#include "Mediator.h"

map<int, Vector2T<int>> Mediator::_walls = {};
map<string, Vector2T<int>> Mediator::_teamsSpawnZones = {};
map<string, list<int>> Mediator::_teams = {};
map<int, Vector2T<int> > Mediator::_tanks = {};
map< int, int > Mediator::_incomingHits = {};
int Mediator::_currentEnemyId = 0;
map<int, int> Mediator::_pastEnemyId = {};

void Mediator::initSpawnZones(int maxWidth, int maxHeight)
{
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("ColorA", { 1 , 1 }));
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("ColorB", { 1 , maxHeight - SpawnRange - 1 }));
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("ColorC", { maxWidth - SpawnRange - 1 , 1 }));
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("ColorD", { maxWidth - SpawnRange - 1 , maxHeight - SpawnRange - 1 }));

}

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

void Mediator::registerMapObject(int id, Vector2T<int> pos, int health)
{
	if (_walls.count(id) == 0)
	{
		_walls.insert(pair<int, Vector2T<int>>(id, pos));
		_incomingHits.insert(pair<int, int>(id, health)); // inregistram un tank cu damage-ul initial primit 0
	}
	else
	{
		_walls[id] = pos;
	}
}

void Mediator::removeMapObject(int id)
{
	_walls.erase(id);
	_incomingHits.erase(id);
}

void Mediator::registerTank(Vector2T<int> pos, int id, int health)
{
	if (_tanks.count(id) == 0)
	{
		_tanks.insert(pair<int, Vector2T<int>>(id, pos));
		_incomingHits.insert(pair<int, int>(id, health)); // inregistram un tank cu damage-ul initial primit 0
	}
	else
	{
		_tanks[id] = pos;
	}
}
void Mediator::removeTank(int tankId, string team)
{
	_tanks.erase(tankId);
	_incomingHits.erase(tankId);
	_pastEnemyId.erase(tankId);
}

bool Mediator::stillExist(int id)
{
	if (_tanks.count(id))
	{
		return true;
	}
	if (_walls.count(id))
	{
		return true;
	}

	return false;
}

void Mediator::notifyTeam(int tankId, string colorTeam)
{
	_teams[colorTeam].push_back(tankId);
}

void Mediator::removeFromTeam(int tankId, string colorTeam)
{

	_teams[colorTeam].remove(tankId);
}

bool Mediator::checkTeammates(int tankId1, int tankId2)
{
	bool areTeamMates = false;
	for (auto& team : _teams)
	{
		std::list<int>::iterator it1 = find(team.second.begin(), team.second.end(), tankId1);
		std::list<int>::iterator it2 = find(team.second.begin(), team.second.end(), tankId2);
		if (it1 != team.second.end() && it2 != team.second.end())
		{
			areTeamMates = true;
		}
	}
	return areTeamMates;
}

Vector2T<int> Mediator::getNearestEnemyPosition(int  id, string colorTeam)
{
	float distance = INFINITY;
	for (auto& i : _teams)
	{
		if (i.first != colorTeam)
		{
			for (auto& j : i.second)
			{
				if (j != id && Mediator::stillExist(j))
				{
					if (Distances::eucliadianDistance(getPosition(id), getPosition(j)) < distance)
					{
						distance = Distances::eucliadianDistance(getPosition(id), getPosition(j));
						_currentEnemyId = j;
					}
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

bool Mediator::checkForEnemies(int id, string colorTeam)
{
	for (auto& team : _teams)
	{
		if (team.first != colorTeam)
		{
			for (auto& playerId : team.second)
			{
				if (Mediator::stillExist(playerId))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Mediator::registerHit(int tankHitted, int damage)
{
	_incomingHits[tankHitted] -= damage;
}

int Mediator::getHealth(int id)
{
	int health = _incomingHits[id];

	if (health <= 0)
	{
		_incomingHits.erase(id);
	}

	return health;
}
