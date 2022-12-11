#pragma once

#include"Vector2i.h"
#include<map>
#include<vector>

using namespace std;

/*Destriere clasa
	 -> clasa ce are ca scop managementul interactiunilor dintre obiecte;
	-> tank-urile sunt identificate dupa _id si o c=echipa
	-> gloatele fiecarui tank sunt identificate tank id si bullet id

*/
class Mediator
{
	static map<const char*  , vector<int> > _teams;
	static map<int, Vector2T<int> > _tanks;
	static map<  pair<int, int>, Vector2T<int> > _bullets;

public:
	static int _currentEnemyId;


	static vector<Vector2T<int>> recieveTanksPosition(int tankId); // pentru coliziunile intre tank-uril

	static void notifyTanksPosition(Vector2T<int> pos, int id); // inregistreaza sau actualizeaza pozitia unui tank
	static void removeTanksPosition(int tankId); // elimina un tank

	static 	void notifyBulletsPosition(Vector2T<int> pos, int tankId, int bulletId); // inregistreaza sau actualizeaza pozitia unui tank
	static void removeBulletsPosition(int tankId, int bulletId); 

	static void notifyTeam(int tankId, const char* colorTeam); // inregistrarea unui tank intr-o echipa
	static void removeFromTeam(int tankId , const char* colorTeam); 

	static Vector2T<int> getNearestEnemyPosition(int  id, const char* colorTeam); // returneaza pozitia celui mai apropiat tank inamic
																				  // calculand o distanta euclidiana
	
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

