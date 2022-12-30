#pragma once

#include"Vector2i.h"
#include<map>
#include<vector>
#include<list>
#include"TimeManager.h"

using namespace std;

#define SpawnRange 8

/*Destriere clasa
	-> clasa ce are ca scop managementul interactiunilor dintre obiecte;
	-> inregistreaza obiecte dupa anumite caracteristi comune
*/
class Mediator
{

	static int _mainPlayerId;

	static map<int, Vector2T<int>> _objects; // contine toate pozitiile wall-urilor
	static map<int, Vector2T<int> > _tanks; // contine pozitiile tuturor tank-urilor
	static map<string, Vector2T<int> > _teamsSpawnZones; // contine pentru fiecare echipa zona in care
														 // se vor spawna tank-urile
	static map<string, list<int> > _teams; // contine maparea tank-urilor pe echipe
	static map<string, int> _teamsPoints;  //contine toate puntele cumulate de echipa
	static map<int, int> _objectsHealth;	   // contine id-ul unui obiect si damage-ul sau primit
	static map<int, int> _killers; // fiecare obiect va avea un killer
	static map<int, string> _activeAbilities; // fiecare tankPoate avea O abilitate activa

public:

	static int getId(Vector2T<int> position);

	/*
		
	*/
	static void setMainPlayerId(int id);

	static bool isMainPlayer(int id);

	/*
		-> initializeaza pozitiile zonele echipelor ;
	*/
	static void init(int maxWidth , int maxHeight);

	static Vector2T<int> getSpawnZone(string teamColor)
	{
		return _teamsSpawnZones[teamColor];
	}
		
	/*
		-> inregistreaza un zid
	*/
	static void registerMapObject(int id , Vector2T<int> pos , int health = 0);

	/*
		-> elimina un zid
	*/
	static void removeMapObject(int id);

	/*
		-> inregistreaza pozitia unui tank
	*/
	static void registerTank(Vector2T<int> pos, int id , int health = 0);
	/*
		-> elimina tot ce este legat de un tank
	*/
	static void removeTank(int tankId , string team);

	/*
	*	-> verifica daca un tank mai exista sau nu 
	*/
	static bool stillExist(int tankId);

	/*
		-> inregistreaza un tank intr-o echipa
	*/
	static void notifyTeam(int tankId, string colorTeam);

	/*
		-> elimina un tank dintr-o echipa
	*/
	static void removeFromTeam(int tankId, string colorTeam);

	static bool checkTeammates(int tankId1, int tankId2);
	
	/*
		-> calculand distante returneaza pozitia celului mai apropiat enemy
	*/
	static Vector2T<int> getNearestEnemyPosition(int  id, string colorTeam);
	
	/*
		-> verifica daca mai este sau nu vreun inamic 
	*/
	static bool checkForEnemies(int id, string colorTeam);
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
	static void modifyHealth(int id, int value);
	/*
		-> returneaza damage-ul primit 
	*/
	static int getHealth(int tankId);

	/*
		-> inregistreaza un killer
	*/
	static void registerKiller(int id, int killer);

	static int getKiller(int id);

	static bool hasKiller(int);


	static string getColorTeam(int id);

	static Vector2T<int> getPosition(int id);

	static map<int, Vector2T<int>>getTanksPositions()
	{
		return _tanks;
	}



	static void addPoint(string color);
	static int getTeamScore(string);


	/*
	* 
	*/
	static bool hasActiveAbility(int id);
	/*
	 
	*/
	static void addAbility(int id, string ability);

	/*
		
	*/
	static string getAbility(int id);

	static void eraseAbility(int id);
};

