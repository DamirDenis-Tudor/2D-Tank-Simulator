#pragma once

#include"Vector2i.h"
#include<map>
#include<vector>

using namespace std;

/*Destriere clasa
	 -> clasa ce are ca scop managementul
	  interactiunilor dintre obiecte;

	-> tank-urile sunt identificate dupa _id
	-> gloatele fiecarui tank sunt identificate tank id si bullet id

	Exemplu:
		- tank1 id: 19 si lanseaza 2 gloate cu id-urile 200 , 201
		- tank2 id: 23 si lanseaza 3 gloate cu id-urile 300 , 301 , 302

		_tanks = {19 , pos} , {23 , pos}
		_bullets = {pair(19 , 200)  , pos} , {pair(19 , 201)  , pos} ...
*/

class Mediator
{
	static map<const char*  , vector<int> > _teams;
	static map<int, Vector2T<int> > _tanks;
	static map<  pair<int, int>, Vector2T<int> > _bullets;

public:
	static int _currentEnemyId;


	static vector<Vector2T<int>> recieveTanksPosition(int tankId); // pentru coliziunile intre tank-uril

	static void notifyTanksPosition(Vector2T<int> pos, int id);
	static void removeTanksPosition(int tankId); //cand un tank este distrus

	static 	void notifyBulletsPosition(Vector2T<int> pos, int tankId, int bulletId);
	static void removeBulletsPosition(int tankId, int bulletId); //cand bullet-ul are coliziune cu ceva

	static void notifyTankTeam(int tankId, const char* colorTeam);
	static void removeTankFromTeam(int tankId , const char* colorTeam);

	static Vector2T<int> getNearestEnemyPosition(int  id, const char* colorTeam);
	
	static Vector2T<int> getPosition(int id)
	{
		return _tanks[id];
	}

	static int getId(Vector2T<int> position)
	{
		for (auto &i : _tanks)
		{
			if (i.second == position)
			{
				return i.first;
			}
		}
		return 0;
	}
	
};

