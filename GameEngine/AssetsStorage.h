#pragma once

#include<map>
#include<vector>
#include<list>
#include<string>
#include<set>
#include"tinyxml2.h"
#include"SpriteComponent.h"

#include<iostream>

using namespace std;
using namespace tinyxml2;

/*
*	sprites : bodies , cannons , bullet 
	Sprites are loaded to a map via an id = [ {"Body" , "Color" , "Type" } ]  => bodySprite.
	For bullet Color is empty .
*/

class AssetsStorage
{
private:

	//static AssetsStorage* _instance;
	AssetsStorage(){}

public:

	static map<set< string >, SpriteComponent* > _movebles; 
	
	static int _mapTileDim ;
	static vector<SpriteComponent * >  _tiles; 

	static int _layerWidth;
	static int _layerHeight;
	static map<string, vector<vector<int>> > _mapLayers;

	static map<string, vector<SpriteComponent*>> _effects;

	static void loadMovebles(const char* sourceFile);
	static SDL_Point* _rotCenter;

	static void loadTiles(const char* sourceFile);
	static void convertInToMatrix(const char* buffer, std::vector<std::vector<int>>& mapLayer);

	static void loadEffects(const char* sourceFile);
};