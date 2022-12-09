#include "Mediator.h"

map<const char*, vector<int>> Mediator::_teams = {};
map<int, Vector2T<int> > Mediator::_tanks = {};
map<  pair<int, int>, Vector2T<int> > Mediator::_bullets = {};
int Mediator::_currentEnemyId = 0;

/*
	Descriere :
		-> returneaza catre tank-ul cu id-ul "tankId"
		pozitiile tuturor tak-urilor
*/
vector<Vector2T<int>> Mediator::recieveTanksPosition(int tankId)
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

void Mediator::notifyTanksPosition(Vector2T<int> pos, int id)
{

	/*
		Descriere:
			-> introduce sau reactualizeaza pozitia unui tank
	*/
	if (_tanks.count(id) == 0)
	{
		_tanks.insert(pair<int, Vector2T<int>>(id, pos));
	}
	else
	{
		_tanks[id] = pos;
	}
}
void Mediator::removeTanksPosition(int tankId)
{
	_tanks.erase(tankId);
}


void Mediator::notifyBulletsPosition(Vector2T<int> pos, int tankId, int bulletId)
{
	/*
	* 		Descriere:
			-> introduce sau reactualizeaza pozitia unui bullet
			   in functie de id-ul posesorului(tank-ului)
	*/
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

void Mediator::removeBulletsPosition(int tankId, int bulletId)
{
	pair<int, int> pairId = { tankId , bulletId };
	_bullets.erase(pairId);
}

void Mediator::notifyTankTeam(int tankId, const char* colorTeam)
{
	_teams[colorTeam].push_back(tankId);
}

void Mediator::removeTankFromTeam(int tankId, const char* colorTeam)
{

	_teams[colorTeam].erase(_teams[colorTeam].begin() + tankId);
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
	return getPosition(_currentEnemyId);
}

