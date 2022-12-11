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
		-> clasa nu poate fi instantiata, reprezinta doar un spatiu de depozitare
		-> contine : tile-uri , sprite-uri pentru bullet , tank , layerele , efecte etc.
		-> foloseste libraria tinyxml2, aceasta trasforma fisirul intr-un arbore;
		-> aplicatia Tiled genereaza o mapa cu un numar de matrici
		   corespunzatoare numarului de layere + locatiile si carateristicile
		   sprite-urilor
		
		-> exemplu de acesare
			-_movebles = map cu id-ul o multime si continutul un sprite
				> acces bullet : _movebles[{"Type1" , "bullet"}];
				> acces body : _movebles[{"ColorA" , "Type1" , "body"}];
			- _mapLayers = map cu id-ul layerului ca indetificator si continul o matrice
				> layer = _mapLayers["ground"]
			- _effects = map cu id-ul effectului ca indetificator si continutul un vector de Sprite-uri
				> effect = _effects["BigExplosion"]

	Nota:
		Tipurile au formatul : "Type1" , ... , "Type8"
		Culorile au formatul : "ColorA" , ... , "ColorD"
		Layerele au formatul : "ground" , "decor" , "colidble"
		Effectele au formatul : "BigExplosion" , "Shot1" , "Impact1"


*/
class AssetsStorage
{
private:

	AssetsStorage() {}

public:
	static map<set< string >, SpriteComponent* > _movebles;//bodies , tracks , cannons , bullets

	static int _mapTileDim; //dimeniunea unui tile de pe mapa
	static vector<SpriteComponent* >  _tiles;

	static int _layerWidth;
	static int _layerHeight;
	static map<string, vector<vector<int>> > _mapLayers;

	static map<string, vector<SpriteComponent*>> _effects;
	static SDL_Point* _rotCenter; // centrul de rotaie al tank-ului

	static void loadMovebles(const char* sourceFile);
	static void loadTiles(const char* sourceFile);
	static void convertInToMatrix(const char* buffer, vector<vector<int>>& mapLayer);
	static void loadEffects(const char* sourceFile);
	static void clear();

};