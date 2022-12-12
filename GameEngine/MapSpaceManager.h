#pragma once

#include"AssetsStorage.h"
#include<queue>
#include"Vector2i.h"
#include"Mediator.h"
#include"ColisionManager.h"

struct Moves
{
	bool _up = false;
	bool _down = false;
	bool _right = false;
	bool _left = false;
	bool _shoting = false;
};

class Node
{
public:
	friend class MapSpaceManager;
	bool _isObstacle = false;
	bool _isVisited = false;
	Vector2T<int> _position = { 0 , 0 };

	float _localGoal = 0.f; // distanta efectiva 

	float _gloabalGoal = 0.f; // ajuta in a seta  o directie
							  // in selectarea nodurilor 

	Node* _parent = nullptr;  // ajuta in refacerea drumului gasit
							  // incepand de la nodul de final

	vector<Node*> _neighbours = {}; 

	Node() {};
	Node(Vector2T<int> position) : _position(position) {}
	~Node()
	{
		for (auto &i : _neighbours)
		{
			i = nullptr;
		}
		_neighbours.clear();
	}

};

/*
	Descriere clasa:
		->responsabila cu gestionarea spatiunlui de pe mapa
			- trasee de urmat
			- pozitii de spawn
*/
class MapSpaceManager
{
	static vector<vector<Node*>> _nodes;
	static Node* _pastEndPos;
public:

	/*
		-> transforma matricea de indici intr-o matrice de noduri
		-> pentru fiecare nod seteaza vecinii
	*/
	static void initNodes();

	/*
		-> reseteaza distantele calculate si statusul "_isVisited" pentru diecare nod
	*/
	static void resetNodes();
	
	static Node* getNode(Vector2T<int> position);
	
	/*
		->simuleaza traseul unui bullet avand sursa: shotter si destinatia: target
	*/
	static bool simulateBulletTrajectory(Vector2T<int> shotter, Vector2T<int>target);

	/*
		-> cauta in raza nodului end(acesta este modificat sau nu) un nod optimal in functie de:
			- distanta dintre el si nod-ul curent al tank-ului
			- obstacolele din range 
			- posibilitatea de tragere
	*/
	static void checkNearestNodeInRange(int tankId , Node* start, Node*& end , int range = 6); 
	
	/*
		-> activeaza sau dezantiveala pozitiile obstacolelor temporare(tank-urile)
	*/
	static void actualizeTemporaryObstacles(int taniId, bool status); 
	
	/*
		distanta manhhatan sau euclidiana dintre 2 noduri
	*/
	static float heuristic(Node* a, Node* b);

	/*
		Descriere aStar:
		-> true - bulletul isi atinge tinta
		-> false - in cazul in care intalnim un obstacol pe drum
	*/
	static Moves aStar(Node* start, Node* end , int tankId);

	static void clear();
};
