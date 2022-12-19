#pragma once

#include"Vector2i.h"
#include<map>
#include<vector>
#include<list>
//#include"AssetsStorage.h"

using namespace std;

/*Destriere clasa
	 -> clasa ce are ca scop managementul interactiunilor dintre obiecte;
	-> tank-urile sunt identificate dupa _id si o echipa
	-> gloatele fiecarui tank sunt identificate tank id si bullet id
	-> de asemenea se trimit notificari legate de lovituri
*/
class Mediator
{
	#define SpawnRange 10

	static map<int, Vector2T<int>> _walls; // contine toate pozitiile wall-urilor
	static map<int, Vector2T<int> > _tanks; // contine pozitiile tuturor tank-urilor
	static map<string, Vector2T<int> > _teamsSpawnZones; // contine pentru fiecare echipa zona in care
														 // se vor spawna tank-urile
	static map<const char*, list<int> > _teams; // contine maparea tank-urilor pe echipe
	static map<  pair<int, int>, Vector2T<int> > _bullets; // contine poziitiile tuturor gloatelor mapate in funtie de un posesor
	static map<int, int> _incomingHits; // contine id-ul unui obiect si damage-ul sau primit

public:

	/*
		-> initializeaza pozitiile zonele echipelor ;
	*/
	static void initSpawnZones(int maxWidth , int maxHeight);

	static Vector2T<int> getSpawnZone(const char* teamColor)
	{
		return _teamsSpawnZones[teamColor];
	}
		
	/*
		-> inregistreaza un zid
	*/
	static void registerWall(int id , Vector2T<int> pos);

	/*
		-> elimina un zid
	*/
	static void removeWall(int id);

	/*
		-> inregistreaza pozitia unui tank
	*/
	static void notifyTankPosition(Vector2T<int> pos, int id);
	/*
		-> elimina tot ce este legat de un tank
	*/
	static void removeTank(int tankId , const char* team);

	/*
	*	-> verifica daca un tank mai exista sau nu 
	*/
	static bool stillExist(int tankId);

	/*
		-> inregistreaza pozitia unui bullet
	*/
	static 	void notifyBulletPosition(Vector2T<int> pos, int tankId, int bulletId);

	/*
		-> elimina posibilitatea de a mai actualiza pozitia unui bullet
	*/
	static void removeBulletPosition(int tankId, int bulletId);

	/*
		-> inregistreaza un tank intr-o echipa
	*/
	static void notifyTeam(int tankId, const char* colorTeam);

	/*
		-> elimina un tank dintr-o echipa
	*/
	static void removeFromTeam(int tankId, const char* colorTeam);

	/*
		-> calculand distante returneaza pozitia celului mai apropiat enemy
	*/
	static Vector2T<int> getNearestEnemyPosition(int  id, const char* colorTeam);
	static int _currentEnemyId;
	static map<int, int> _pastEnemyId;

	/*
		-> returneaza un vector cu toate pozitiile tank-urilor
		   exceptand pozitia solicitantului
	*/
	static vector<Vector2T<int>> recieveTanksPositions(int tankId);

	/*
		-> inregistreaza un damage unui tank
	*/
	static void registerHit(int tankHitted, int damage);
	/*
		-> returneaza damage-ul primit 
	*/
	static int checkForDamage(int tankId);

	static string getColorTeam(int id)
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

	static Vector2T<int> getPosition(int id)
	{
		if (_tanks.count(id) != 0)
		{
			return _tanks[id];
		}
		if (_walls.count(id) != 0)
		{
			return _walls[id];
		}
		return { -1 , -1 };
	}

	static int getId(Vector2T<int> position)
	{
		for (auto& i : _tanks)
		{
			if (i.second == position)
			{
				return i.first;
			}
		}

		for (auto& i : _walls)
		{
			if (i.second == position)
			{
				return i.first;
			}
		}

		return 0;
	}

	static map<int, Vector2T<int>>getTanksPositions()
	{
		return _tanks;
	}

};

