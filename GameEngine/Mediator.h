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
	static int _targetId;
	static map<int, Vector2T<int> > _tanks;
	static map<  pair<int, int>, Vector2T<int> > _bullets;

public:

	static vector<Vector2T<int>> recieveBulletsPosition(int tankId, int bulletId);

	static vector<Vector2T<int>> recieveTanksPosition(int tankId);

	static void notifyTanksPosition(Vector2T<int> pos, int id);

	static 	void notifyBulletsPosition(Vector2T<int> pos, int tankId, int bulletId);

	static void removeBulletsPosition(int tankId, int bulletId);

	static void removeTanksPosition(int tankId);

	static void setPlayerId(int id)
	{
		_targetId = id;
	}

	static int getPlayerId()
	{
		return _targetId;
	}

	static Vector2T<int> getTargetPosition()
	{
		return _tanks[_targetId];
	}

	static Vector2T<int> getPosition(int id)
	{
		return _tanks[id];
	}
	
};

