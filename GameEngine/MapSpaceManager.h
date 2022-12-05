#pragma once

#include"AssetsStorage.h"
#include<queue>
#include"Vector2i.h"

class Node
{
	friend class MapSpaceManager;
	bool _isObstacle = false;
	bool _isVisited = false;
	Vector2T<int> _position = { 0 , 0 };

	float _localGoal = 0.f;
	float _gloabalGoal = 0.f;

	Node* _parent = nullptr;
	vector<Node*> _neighbors = {};
public:
	Node() {};
	Node(Vector2T<int> position) : _position(position) {}
	~Node()
	{
		delete _parent;
		_parent = nullptr;

		for (auto &i : _neighbors)
		{
			i = nullptr;
		}
		_neighbors.clear();
	}

};

class MapSpaceManager
{
	static vector<vector<Node*>> _nodes;
public:

	static void initNodes();
	
	static float eucliadianDistance(Node* a, Node* b);
	static  float manhhatanDistance(Node* a, Node* b);
	static float heuristic(Node* a, Node* b);
	
	static Node* getNode(Vector2T<int> position);
	
	static void aStar(Node* start, Node* end);

	static void clear();
};
