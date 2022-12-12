#include"ColisionManager.h"

void CollisionManager::mapCollision(Vector2T<float>& potentialPos)
{
	int startCellX = std::max(0, (int)(potentialPos.getX()) / AssetsStorage::_tileDim - 1);
	int endCellX = std::min(AssetsStorage::_layerWidth - 1, (int)(potentialPos.getX()) / AssetsStorage::_tileDim + 1);

	int startCellY = std::max(0, (int)(potentialPos.getY()) / AssetsStorage::_tileDim - 1);
	int endCellY = std::min(AssetsStorage::_layerHeight - 1, (int)(potentialPos.getY()) / AssetsStorage::_tileDim + 1);

	for (int i = startCellY; i <= endCellY; i++)
	{
		for (int j = startCellX; j <= endCellX; j++)
		{
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				Vector2T<int> rectPos = { j * AssetsStorage::_tileDim , i * AssetsStorage::_tileDim };

				circleRectagleCollision(potentialPos, rectPos, AssetsStorage::_tileDim);
			}
		}
	}
}

bool CollisionManager::circleRectagleCollision(Vector2T<float>& potentialPos, Vector2T<int>& rectaglePos, int& rectagleDim)
{
	int colision = false;
	Vector2T<float> nearestPoint;
	nearestPoint.setX(std::max(float(rectaglePos._x),
		std::min(float(potentialPos._x), float(rectaglePos._x + rectagleDim))));

	nearestPoint.setY(std::max(float(rectaglePos._y),
		std::min(float(potentialPos._y), float(rectaglePos._y + rectagleDim))));

	// calculam punctul de inceput
	// al diferentei de lungime 

	Vector2T<float> rayToNearest = nearestPoint - potentialPos;

	//calculam distanta pana
	//la cel mai apropiat punct 

	float nearestPointDistance = rayToNearest.mag();

	// "comparam" distanta cu raza cercului

	float fOverlap = AssetsStorage::_tileDim - nearestPointDistance;

	if (std::isnan(fOverlap))
	{
		fOverlap = 0;
	}

	//daca overlap-ul este mai mare s-a produs coliziunea => trebuie corectat;

	if (fOverlap > 0)
	{

		Vector2T<float> normToNearest = rayToNearest / nearestPointDistance;

		//recalibram obiectul 
		potentialPos = potentialPos - normToNearest * fOverlap;
		colision = true;
	}

	return colision;
}

bool CollisionManager::pointCollisionMap(Vector2T<float>& potentialPos)
{
	if (AssetsStorage::_mapLayers["colidble"][static_cast<int>(potentialPos._y / AssetsStorage::_tileDim)][static_cast<int>(potentialPos._x / AssetsStorage::_tileDim)] != 0)
	{
		return true;
	}
	return false;
}

bool CollisionManager::pointCollisionRectagle(Vector2T<float> potentialPos, Vector2T<int> rectPos, int rectDim)
{
	if (potentialPos._x > rectPos._x && potentialPos._y > rectPos._y &&
		potentialPos._x < rectPos._x + rectDim  && potentialPos._y < rectPos._y + rectDim)
	{
		return true;
	}
	return false;
}
