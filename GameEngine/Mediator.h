#pragma once

#include"Vector2i.h"
#include<map>
#include<vector>

using namespace std;

class Mediator
{
	static map<int, Vector2T<int> > _tanks;
	static map<  pair<int, int>, Vector2T<int> > _bullets;

public:

	static vector<Vector2T<int>> recieveBulletsPosition(int tankId, int bulletId)
	{
		//vector<Vector2T<int>> enemyBullets;

		//for (auto& i : _bullets)
		//{
		//	if (i.first != pair<int, int>(tankId, bulletId))
		//	{
		//		enemyBullets.push_back(i.second);
		//	}
		//}
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

	static 	void notifyBulletsPosition(Vector2T<int> pos, int id)
	{

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
