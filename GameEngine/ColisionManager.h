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
	
	static bool circleCollision(Vector2T<float>& potentialPos);
	static bool pointCollision(Vector2T<float>& potentialPos);
};
