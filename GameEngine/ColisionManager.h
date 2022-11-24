#pragma once

#include"Vector2i.h"
#include"AssetsStorage.h"
#include"iostream"

class CollisionManager
{
private:

	CollisionManager() {};

public:
	~CollisionManager() {};
	
	static bool mapCollision(Vector2T<float>& potentialPos);

};
