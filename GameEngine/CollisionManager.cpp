#include"ColisionManager.h"

bool CollisionManager::circleCollision(Vector2T<float>& potentialPos)
{
	bool colision = false;
	//spatiul de detectare a coliziunilor => 2 X 2

	int startCellX = std::max(0, (int)(potentialPos.getX()) / AssetsStorage:: _mapTileDim - 1);
	int endCellX = std::min(AssetsStorage::_layerWidth - 1, (int)(potentialPos.getX()) / AssetsStorage::_mapTileDim + 1);

	int startCellY = std::max(0, (int)(potentialPos.getY()) / AssetsStorage::_mapTileDim - 1);
	int endCellY = std::min(AssetsStorage::_layerHeight - 1, (int)(potentialPos.getY()) / AssetsStorage::_mapTileDim + 1);

	for (int i = startCellY; i <= endCellY; i++)
	{
		for (int j = startCellX; j <= endCellX; j++)
		{
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				/*
				//	calculam cel mai apropiat punct
				//	de cerc nostru

				//	incadram punctul cel mai apropiat
				//	in spatiul de coliziune al obiectului
					  _________________________________
					  |				                  |
			  point(*)|<-	  spatiul de coliziune  ->|
					  |_______________________________|
				*/

				Vector2T<float> nearestPoint;
				nearestPoint.setX(std::max(float(j * AssetsStorage::_mapTileDim),
					std::min(float( potentialPos.getX() ), float((j + 1) * AssetsStorage::_mapTileDim))));
				
				nearestPoint.setY(std::max(float(i * AssetsStorage::_mapTileDim),
					std::min(float(potentialPos.getY()), float((i + 1) * AssetsStorage::_mapTileDim))));


				// calculam punctul de inceput
				// al diferentei de lungime 

				Vector2T<float> rayToNearest = nearestPoint - potentialPos;

				//calculam distanta pana
				//la cel mai apropiat punct 

				float nearestPointDistance = rayToNearest.mag();

				// "comparam" distanta cu raza cercului

				float fOverlap = AssetsStorage::_mapTileDim - nearestPointDistance;

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

			}
		}
	}
	return colision;
}

bool CollisionManager::pointCollision(Vector2T<float>& potentialPos)
{
	if (AssetsStorage::_mapLayers["colidble"][static_cast<int>(potentialPos._y / AssetsStorage::_mapTileDim) ][static_cast<int>(potentialPos._x / AssetsStorage::_mapTileDim)] != 0)
	{
		return true;
	}
	return false;
}