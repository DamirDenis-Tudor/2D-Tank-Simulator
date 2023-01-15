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
			etc.

	Nota:
		Tipurile au formatul : "Type1" , ... , "Type8"
		Culorile au formatul : "ColorA" , ... , "ColorD"
		Layerele au formatul : "ground" , "decor" , "colidble"
		Effectele au formatul : "BigExplosion" , "Shot1" , "Impact1"
		Abilitatile au formatul : "ShootingBoost" , "HealthBoost , "SpeedBoost"
		Minele au formatul: "Yellowmine" etc
		Exploziile minelor au formatul : BluemineExplosion etc
*/
class AssetsStorage
{
private:

	AssetsStorage() {}

public:
	static int _tileDim; //dimeniunea unui tile de pe mapa
	static int _barrelId; // identificator de id pentru barrel
						  // simplifica cu mult crearea unui obiect de tip barrel 
	static int _layerWidth;
	static int _layerHeight;
	static SDL_Point* _rotCenter; // centrul de rotaie al tank-ului

	static map<string, vector<vector<int>> > _mapLayers;
	static map<string, SpriteComponent*> _menuItems;
	static vector<SpriteComponent* > _tiles;
	static map<string, SpriteComponent* > _miniMapTiles;
	static map<set< string >, SpriteComponent* > _movebles;//bodies , tracks , cannons , bullets
	static map<string, vector<SpriteComponent*>> _effects;
	static map<string, SpriteComponent*> _abilities;

	static void loadMap(const char* sourceFile);
	static void loadMenu(const char* sourceFile);
	static void loadSprites(const char* sourceFile);
	static void loadAbilities(const char* sourceFile);
	static void loadMiniTiles(const char* sourceFile);

	static void convertInToMatrix(const char* buffer, vector<vector<int>>& mapLayer);
	static void loadEffects(const char* sourceFile);

	static void clearMap();
	static void clear();

};