#pragma once

#include"Vector2i.h"
#include<map>
#include<vector>

using namespace std;

//ai grija sa scoti tank-urile daca sunt disable

//daca nu vrea collisiuni bullets bullets scot bullets

class Mediator
{
	static int _targetId;
	static map<int, Vector2T<int> > _tanks;
	static map<  pair<int, int>, Vector2T<int> > _bullets;

public:

	static vector<Vector2T<int>> recieveBulletsPosition(int tankId, int bulletId)
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

	static vector<Vector2T<int>> recieveTanksPosition(int tankId)
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

	static void notifyTanksPosition(Vector2T<int> pos, int id)
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

	static 	void notifyBulletsPosition(Vector2T<int> pos, int tankId , int bulletId)
	{
		pair<int, int> idPair = {tankId , bulletId};
		if (_bullets.count( idPair ) == 0) //daca nu a mai fost inregistrat
		{
			_bullets.insert(pair<pair<int , int>, Vector2T<int> >(idPair , pos));
		}
		else //daca da doar modifcam pozitia
		{
			_bullets[idPair] = pos;
		}
	}

	static void removeBulletsPosition(int tankId, int bulletId)
	{
		pair<int , int> pairId = { tankId , bulletId };
		_bullets.erase(pairId);
	}

	static void removeTanksPosition(int tankId)
	{
		_tanks.erase(tankId);
	}

	static void setPlayerId(int id)
	{
		_targetId = id;
	}

	static Vector2T<int> getTargetPosition()
	{
		return _tanks[_targetId];
	}
};

//notite
/*
	-> tank-urile sunt identificate dupa _id
	-> gloatele fiecarui tank sunt identificate tank id si bullet id

	Exemplu:
		- tank1 id: 19 si lanseaza 2 gloate cu id-urile 200 , 201
		- tank2 id: 23 si lanseaza 3 gloate cu id-urile 300 , 301 , 302

		_tanks = {19 , pos} , {23 , pos}
		_bullets = {pair(19 , 200)  , pos} , {pair(19 , 201)  , pos} ...




*/
