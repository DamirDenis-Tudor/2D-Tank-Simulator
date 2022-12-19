#pragma once
#include"Vector2i.h"
#include"RendererManager.h"
#include"Mediator.h"

/*
	Descrierea clasei:
		-> primeste un obiect de urmarit;
		-> implemeteaza o metoda de sincronizare
		-> calculeaza offset-urile 
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
	static Vector2T<int> tileOffset; // offset - pastOffset

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

