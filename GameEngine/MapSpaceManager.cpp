#include "MapSpaceManager.h"

//alocam o matrice intr-o zona continua de memorie
vector<vector<Node*>> MapSpaceManager::_nodes = {};

void MapSpaceManager::initNodes()
{
	//initializam toate nodurile
	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		vector<Node*> nodes;
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			Node* node = new Node({ i , j });
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				node->_isObstacle = true;
			}
			nodes.push_back(node);
		}
		_nodes.push_back(nodes);
}

	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth ; j++)
		{
			//nodurile sus jos stanga dreapta
			if (j > 0)
			{
				_nodes[i][j]->_neighbors.push_back(_nodes[i][j - 1]);
			}
			if (j < AssetsStorage::_layerWidth - 1)
			{
				_nodes[i][j]->_neighbors.push_back(_nodes[i][j + 1]);
			}
			if (i > 0)
			{
				_nodes[i][j]->_neighbors.push_back(_nodes[i - 1][j]);
			}
			if (i < AssetsStorage::_layerHeight - 1)
			{
				_nodes[i][j]->_neighbors.push_back(_nodes[i + 1][j]);
			}

			//de adaugat nodurile pe diagonala
		}
	}
}

float MapSpaceManager::eucliadianDistance(Node* a, Node* b)
{
	return (sqrt((a->_position._x - b->_position._x )* (a->_position._x - b->_position._x )
		+ (a->_position._y - b->_position._y) * (a->_position._y - b->_position._y) ));
}

float MapSpaceManager::manhhatanDistance(Node* a, Node* b)
{
	return 0.0f;
}

float MapSpaceManager::heuristic(Node* a, Node* b)
{
	return eucliadianDistance(a, b);
}

Node* MapSpaceManager::getNode(Vector2T<int> position)
{
	for ( auto &i : _nodes)
	{
		for (auto& j : i)
		{
			if (j->_position == position)
			{
				return j;
			}
		}
	}
	return nullptr;
}


void MapSpaceManager::aStar(Node* start , Node* end)
{
	for (auto& i : _nodes)
	{
		for (auto& j : i)
		{
			j->_isVisited = false;
			j->_localGoal = INFINITY;
			j->_gloabalGoal = INFINITY;
		}
	}
}

void MapSpaceManager::clear()
{
	for (auto &i : _nodes)
	{
		for (auto& j : i)
		{
			delete j;
			j = nullptr;
		}
		i.clear();
	}
}
