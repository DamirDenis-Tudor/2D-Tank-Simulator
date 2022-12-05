#pragma once

#include"AssetsStorage.h"
#include<queue>
#include"Vector2i.h"
#include"Mediator.h"

struct Moves
{
	bool _up = false;
	bool _down = false;
	bool _right = false;
	bool _left = false;
};

class Node
{
public:
	friend class MapSpaceManager;
	//friend std::sort();
	bool _isObstacle = false;
	bool _isVisited = false;
	Vector2T<int> _position = { 0 , 0 };

	float _localGoal = 0.f;
	float _gloabalGoal = 0.f;

	Node* _parent = nullptr;
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

class MapSpaceManager
{
	static vector<vector<Node*>> _nodes;
	static Node* _actualEndNode;
public:

	static void initNodes();
	
	static float eucliadianDistance(Node* a, Node* b);
	static  float manhhatanDistance(Node* a, Node* b);
	static float heuristic(Node* a, Node* b);
	
	static Node* getNode(Vector2T<int> position);
	
	static void resetNodes();
	static void actualizeTemporaryObstacles(int taniId , bool status);
	static void findAreaPos(Node* start , Node* end);
	static Moves aStar(Node* start, Node* end , int tankId);

	static void clear();
};
