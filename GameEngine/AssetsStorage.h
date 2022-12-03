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

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

/*
	Descriere clasa:

		-> foloseste libraria tinyxml2, aceasta trasforma fisirul intr-un arbore;
		-> aplicatia Tiled genereaza o mapa cu un numar de matrici
		   corespunzatoare numarului de layere + locatiile si carateristicile 
		   sprite-urilor

		-> format :

	*
	* <tank ....
	*
	*	<body - atributes
	*		<tileset - atributes ..
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	*	<cannons - atributes
	*		<tileset - atributes
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	*	<bullets - atributes
	*		<tileset - atributes
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	* 	<tracks - atributes
	*			<image - atributes
	*
	* <tank/>
	*
	* 
	
	-> exemplu de acesare dupa citirea din fisier: 
	 -	_movebles = map cu id-ul o multime si continutul un sprite
			> acces bullet : _movebles[{"Type1" , "bullet"}];
			> acces body : _movebles[{"ColorA" , "Type1" , "bullet"}];
			etc.
	- _mapLayers = map cu id-ul layerului ca indetificator si continul o matrice
			> layer = _mapLayers["ground"]
	- _effets = map cu id-ul effectului ca indetificator si continutul un vector de Sprite-uri
			> effect = _effects["BigExplosion"]

	Nota: 
		Tipurile au formatul : "Type1" , ... , "Type8"
		Culorile au formatul : "ColorA" , ... , "ColorD"
		Layerele au formatul : "ground" , "decor" , "colidble"
		Effectele au formaul : "BigExplosion" , "Shot1" , "Impact1"
		
*/

class AssetsStorage
{
private:

	AssetsStorage(){}

public:

	static void clear()
	{
		for (auto x = _movebles.begin();  x != _movebles.end() ; x++)
		{
			delete x->second;
			x->second = 0;
		}
		_movebles.clear();

		for (int i = 0; i < _tiles.size(); i++)
		{
			delete _tiles[i];
			_tiles[i] = 0;
		}
		_tiles.clear();

		for (auto& x : _effects)
		{
			for (int i = 0; i < size(_effects[x.first] ); i++)
			{
				delete _effects[x.first][i];
				_effects[x.first][i] = 0;
			}
			_effects[x.first].clear();
		}
		_effects.clear();

		delete _rotCenter;

	}

	static map<set< string >, SpriteComponent* > _movebles; 
	
	static int _mapTileDim ;
	static vector<SpriteComponent * >  _tiles; 

	static int _layerWidth;
	static int _layerHeight;
	static map<string, vector<vector<int>> > _mapLayers;

	static map<string, vector<SpriteComponent*>> _effects;
	static SDL_Point* _rotCenter ;

	static void loadMovebles(const char* sourceFile);

	static void loadTiles(const char* sourceFile);
	static void convertInToMatrix(const char* buffer, vector<vector<int>>& mapLayer);

	static void loadEffects(const char* sourceFile);
};