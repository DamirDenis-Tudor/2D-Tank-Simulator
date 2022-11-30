#pragma once

#include"Vector2i.h"
#include"AssetsStorage.h"

/*
	Descriere clasa:
		->implemeteaza utilitare pentru diferite tipuri de collisiuni;
*/

class CollisionManager
{
private:

	CollisionManager() {};

public:
	~CollisionManager() {};
	
	static bool mapCollision(Vector2T<float>& potentialPos);
	static bool circleCircleCollision(Vector2T<float>& potentialPos );
	static bool pointCollision(Vector2T<float>& potentialPos);
};
