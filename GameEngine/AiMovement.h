#pragma once
#include "Movement.h"
#include<iostream>

class AiMovement : public Movement
{
	//bullet behavior is the same as InputMovemnet
	Vector2T<float> direction;

	void move(Vector2T<int>& position, Vector2T<float> velocity) override
	{
		Vector2T<float> potentialPos;
		potentialPos.setX(position.getX() + AssetsStorage::_mapTileDim);
		potentialPos.setY(position.getY() + AssetsStorage::_mapTileDim);
		
		//direction.setY(1);
		
		potentialPos += velocity * direction;

		if (!CollisionManager::mapCollision(potentialPos))
		{
		//	direction.setX(1);
		}

		position.setX(static_cast <int>(potentialPos.getX() - AssetsStorage::_mapTileDim));
		position.setY(static_cast <int>(potentialPos.getY() - AssetsStorage::_mapTileDim));

	}

	void rotationC(Vector2T<int>& position, float& agle) override
	{

	}
	void rotationB(float& angle) override
	{

	}
};

