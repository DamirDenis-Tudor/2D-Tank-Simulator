#include "CameraManager.h"

int CameraManager::_tileDim = 0;
int CameraManager::_mapTilesWidth = 0;
int CameraManager::_mapTilesHeight = 0;
int CameraManager::_gameObjectId = 0;
Vector2T<int> CameraManager::offset = { 0,0 };
Vector2T<int> CameraManager::pastOffset = { 0,0 };
Vector2T<int> CameraManager::tileOffset = { 0,0 };


void CameraManager::init(int& tileDim, int& mapTilesWidth, int& mapTilesHeight)
{
	_tileDim = tileDim;
	_mapTilesHeight = mapTilesHeight;
	_mapTilesWidth = mapTilesWidth;
}

void CameraManager::cameraSync()
{
	Vector2T<int> position = Mediator::getPosition(_gameObjectId);
	CameraManager::pastOffset = CameraManager::offset;

	CameraManager::offset.setX(position.getX() + _tileDim - RendererManager::_width / 2);
	CameraManager::offset.setY(position.getY() + _tileDim- RendererManager::_heigth / 2);

	//borders check
	int horizontalBorder = _mapTilesWidth * _tileDim - RendererManager::_width;
	int verticalBorder = _mapTilesHeight * _tileDim- RendererManager::_heigth;
	if (CameraManager::offset.getX() < 0)
	{
		CameraManager::offset.setX(0);
	}
	if (CameraManager::offset.getY() < 0)
	{
		CameraManager::offset.setY(0);
	}
	if (CameraManager::offset.getX() > horizontalBorder)
	{
		CameraManager::offset.setX(horizontalBorder);
	}
	if (CameraManager::offset.getY() > verticalBorder)
	{
		CameraManager::offset.setY(verticalBorder);
	}
	CameraManager::tileOffset = CameraManager::offset - CameraManager::pastOffset;
}
