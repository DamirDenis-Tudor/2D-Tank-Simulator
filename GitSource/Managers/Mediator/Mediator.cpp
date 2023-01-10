#include "Mediator.h"

int Mediator::_mainPlayerId = 0;
map<int, Vector2T<int>> Mediator::_objects = {};
map<string, Vector2T<int>> Mediator::_teamsSpawnZones = {};
map<string, list<int>> Mediator::_teams = {};
map<string, int> Mediator::_teamsPoints = {};
map<int, Vector2T<int> > Mediator::_tanks = {};
map<int, int> Mediator::_killers = {};
map< int, int > Mediator::_objectsHealth = {};
map<int, string> Mediator::_activeAbilities = {};
int Mediator::_currentEnemyId = 0;
map<int, int> Mediator::_pastEnemyId = {};

int Mediator::getId(Vector2T<int> position)
{
	for (auto& i : _tanks)
	{
		if (i.second == position)
		{
			return i.first;
		}
	}

	for (auto& i : _objects)
	{
		if (i.second == position)
		{
			return i.first;
		}
	}

	return -1;
}

string Mediator::getColorTeam(int id)
{
	for (auto& i : _teams)
	{
		list<int>::iterator it;
		it = find(i.second.begin(), i.second.end(), id);
		if (it != i.second.end())
		{
			return i.first;
		}
	}

	return " ";
}

Vector2T<int> Mediator::getPosition(int id)
{
	if (_tanks.count(id) != 0)
	{
		return _tanks[id];
	}
	if (_objects.count(id) != 0)
	{
		return _objects[id];
	}
	return { -11111 , -11111 };
}

void Mediator::setMainPlayerId(int id)
{
	_mainPlayerId = id;
}

bool Mediator::isMainPlayer(int id)
{
	return id == _mainPlayerId ? true : false;
}

void Mediator::init(int maxWidth, int maxHeight)
{
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("Yellow", { 1 , 1 }));
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("Green", { 1 , maxHeight - 1 - SpawnRange }));
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("Blue", { maxWidth - 1 - SpawnRange  , 1 }));
	_teamsSpawnZones.insert(pair<string, Vector2T<int>>("Brown", { maxWidth - 1 - SpawnRange  , maxHeight - 1 - SpawnRange }));

	_teamsPoints.insert(pair<string, int>("Yellow", 0));
	_teamsPoints.insert(pair<string, int>("Green", 0));
	_teamsPoints.insert(pair<string, int>("Blue", 0));
	_teamsPoints.insert(pair<string, int>("Brown", 0));

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
	if (_objects.count(id) == 0)
	{
		_objects.insert(pair<int, Vector2T<int>>(id, pos));
		_objectsHealth.insert(pair<int, int>(id, health)); // inregistram un tank cu damage-ul initial primit 0
	}
	else
	{
		_objects[id] = pos;
	}
}

void Mediator::removeMapObject(int id)
{
	_objects.erase(id);
	_objectsHealth.erase(id);
}

void Mediator::registerTank(Vector2T<int> pos, int id, int health)
{
	if (_tanks.count(id) == 0)
	{
		_tanks.insert(pair<int, Vector2T<int>>(id, pos));
		_objectsHealth.insert(pair<int, int>(id, health)); // inregistram un tank cu damage-ul initial primit 0
	}
	else
	{
		_tanks[id] = pos;
	}
}
void Mediator::removeTank(int tankId, string team)
{
	_tanks.erase(tankId);
	_objectsHealth.erase(tankId);
	_pastEnemyId.erase(tankId);
}

bool Mediator::stillExist(int id)
{
	if (_tanks.count(id))
	{
		return true;
	}
	if (_objects.count(id))
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
	/*
	* se cauta cel mai apropia inamic in range
	*/
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

	/*
	* daca am gasit un inamic se verifica 
	* cu cel precendent(daca mai exista) =>
	* in functie de o toleranta se stabileste 
	* inamicul de urmarit
	*/
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

void Mediator::modifyHealth(int id, int value)
{
	_objectsHealth[id] += value;
	if (_objectsHealth[id] < 0)
	{
		_objectsHealth[id] = 0;
	}
	if (_objectsHealth[id] > 100)
	{
		_objectsHealth[id] = 100;
	}
}

void Mediator::registerKiller(int id, int killer)
{
	if (_killers.count(id) == 0)
	{
		_killers.insert(pair<int, int>(id, killer));
		return;
	}
	_killers[id] = killer;
}

int Mediator::getKiller(int id)
{
	return _killers[id];
}

bool Mediator::hasKiller(int id)
{
	return _killers.count(id) != 0 ? true : false;
}

int Mediator::getHealth(int id)
{
	int health = _objectsHealth[id];

	if (health <= 0)
	{
		_objectsHealth.erase(id);
	}

	return health;
}

void Mediator::addPoint(string team)
{
	_teamsPoints[team]++;
}

int Mediator::getTeamScore(string team)
{
	return _teamsPoints[team];
}


bool Mediator::hasActiveAbility(int id)
{
	return _activeAbilities.count(id) != 0 ? true : false;
}

void Mediator::addAbility(int id, string ability)
{
	_activeAbilities.insert(pair<int, string>(id, ability));
}

string Mediator::getAbility(int id)
{
	return _activeAbilities[id];;
}

void Mediator::eraseAbility(int id)
{
	if (_activeAbilities.count(id) == 0) return;

	TimeManager::_timers[to_string(id) + _activeAbilities[id]]->resetTimer();
	_activeAbilities.erase(id);
}