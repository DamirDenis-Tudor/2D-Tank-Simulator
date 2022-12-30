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
	bool _releaseMine = false;
};

class Node
{
public:
	friend class MapSpaceManager;

	bool _isPermanent = false;
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
			- pozii optimale de tragere
*/
class MapSpaceManager
{
	static int _range; // default 5: shotter-ul va cauta o pozitie la distanta de 5 tile-uri
	static int _curretTankId;
	static string _currentColor;
	static vector<vector<Node*>> _nodes;
	static Node* _pastEndPos;
public:

	static void printMap();

	/*
		-> informeaza managerul despre "utilizatorul" curent
	*/
	static void setUser(int id, string color = "");

	static void setObstacles(Vector2T<int> position, bool status)
	{
		_nodes[position._x][position._y]->_isObstacle = status;
		_nodes[position._x][position._y]->_isPermanent = status;
	}

	/*
		-> transforma matricea de indici intr-o matrice de noduri
		-> pentru fiecare nod seteaza vecinii
	*/
	static void initNodes();

	/*
		-> reseteaza distantele calculate si statusul "_isVisited" pentru fiecare nod
	*/
	static void resetNodes();
	
	/*
		->returneaza o pozitie de spawn pentru un tank
	*/
	static Vector2T<int> getTankSpawnPosition();
	
	/*
		->returneaza  poztie de spawn pentru un obiect
	*/
	static Vector2T<int> getObjectSpawnPosition();

	/*
		-> primeste o pozitie relativa la mapa si returneaza nodul aferent
	*/
	static Node* getNode(Vector2T<int> position);
	
	/*
	*	-> verifica daca corpul unui tank are vreun obstacol(verifica cele 4 tile-uri)
	*	-> primeste ca reper nodul din stanga sus
	*/
	static bool bodyContainsObstacles(Node* body);

	/*
		-> verica daca un nod contine sau nu un obtsacol temporar
	*/
	static bool nodeContainsTemporaryObstacles(Node* node);

	/*
		->simuleaza traseul unui bullet avand sursa: shotter si destinatia: target
		true : are traseu 
		false : are un obstacol pe drum
		-> targetul va fi preluat din Mediator
	*/
	static bool simulateBulletTrajectory(Vector2T<int> shotter);

	/*
		-> cauta in raza nodului end(acesta este modificat sau nu) un nod optimal in functie de:
			- distanta dintre el si nod-ul curent al tank-ului
			- obstacolele din range 
			- posibilitatea de tragere
	*/
	static void checkNearestNodeInRange( Node* start, Node*& end); 
	
	/*
		-> activeaza sau dezantiveala pozitiile obstacolelor temporare(tank-urile)
	*/
	static void actualizeTemporaryObstacles(bool status); 
	
	/*
		distanta manhhatan sau euclidiana dintre 2 noduri
	*/
	static float heuristic(Node* a, Node* b);

	/*
		-> converteste o pozitie in spatiu intr-un nod pe mapa
	*/
	static Node*& nodeConversion(Vector2T<int> position);

	/*
	
	*/
	static bool isInRangeOfTarget(Node* start);

	/*
		-> returneaza primul set de mutari(shooting sau movement) 
	*/
	static Moves aStar(Vector2T<int> start, Vector2T<int> end , bool healing = false);

	/*
		-> are rolul de a spawna abilitay pe mapa
	*/

	static void clear();
};
