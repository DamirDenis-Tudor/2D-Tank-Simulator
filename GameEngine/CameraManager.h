#pragma once
#include"Vector2i.h"
#include"RendererManager.h"
#include"Mediator.h"

/*
	Descrierea clasei:

		->in viitor va implemeta o metoda statica de sync
		si una de zoom in  , out
*/

class CameraManager
{
private:
	CameraManager() {}

	static int _tileDim;
	static int _mapTilesWidth;
	static int _mapTilesHeight;
	static int _gameObjectId;
public:
	static Vector2T<int> offset ;
	static Vector2T<int> pastOffset;
	static Vector2T<int> tileOffset;

	static void init(int& tileDim, int& mapTilesWidth, int& mapTilesHeight);
	static void cameraSync();
	
	static void setFocusId(int id)
	{
		_gameObjectId = id;

	}
	static int getFocusId()
	{
		return _gameObjectId;
	}
};

