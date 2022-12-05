#include "MapSpaceManager.h"

//alocam o matrice intr-o zona continua de memorie
vector<vector<Node*>> MapSpaceManager::_nodes = {};

void MapSpaceManager::initNodes()
{
	//initializam toate nodurile
	for (int i = 0; i < AssetsStorage::_layerWidth; i++)
	{
		vector<Node*> nodes;
		for (int j = 0; j < AssetsStorage::_layerHeight; j++)
		{
			Node* node = new Node({ i , j });
			if (AssetsStorage::_mapLayers["colidble"][j][i] != 0)
			{
				node->_isObstacle = true;
			}
			nodes.push_back(node);
		}
		_nodes.push_back(nodes);
	}

	for (int i = 0; i < AssetsStorage::_layerWidth; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerHeight; j++)
		{
			//nodurile sus jos stanga dreapta
			if (j > 0)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i][j - 1]);
			}
			if (j < AssetsStorage::_layerHeight - 1)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i][j + 1]);
			}
			if (i > 0)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i - 1][j]);
			}
			if (i < AssetsStorage::_layerWidth - 1)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i + 1][j]);
			}

			//de adaugat nodurile pe diagonala
			//if (i > 0 && j > 0)
			//{
			//	_nodes[i][j]->_neighbours.push_back(_nodes[i - 1][j - 1]);
			//}
			//if (i > 0 && j < AssetsStorage::_layerHeight - 1)
			//{
			//	_nodes[i][j]->_neighbours.push_back(_nodes[i - 1][j + 1]);
			//}
			//if (j > 0 && i < AssetsStorage::_layerWidth - 1)
			//{
			//	_nodes[i][j]->_neighbours.push_back(_nodes[i + 1][j - 1]);
			//}
			//if (i < AssetsStorage::_layerHeight - 1 && j < AssetsStorage::_layerHeight - 1)
			//{
			//	_nodes[i][j]->_neighbours.push_back(_nodes[i + 1][j + 1]);
			//}
		}
	}
}

float MapSpaceManager::eucliadianDistance(Node* a, Node* b)
{
	return (sqrt((a->_position._x - b->_position._x) * (a->_position._x - b->_position._x)
		+ (a->_position._y - b->_position._y) * (a->_position._y - b->_position._y)));
}

float MapSpaceManager::manhhatanDistance(Node* a, Node* b)
{
	return abs(a->_position._x - b->_position._x) + abs(a->_position._y - b->_position._y);
}

float MapSpaceManager::heuristic(Node* a, Node* b)
{
	return manhhatanDistance(a,b);
}

Node* MapSpaceManager::getNode(Vector2T<int> position)
{
	return _nodes[position._x][position._y];
}


void MapSpaceManager::resetNodes()
{
	for (auto& i : _nodes)
	{
		for (auto& j : i)
		{
			j->_isVisited = false;
			j->_localGoal = INFINITY;
			j->_gloabalGoal = INFINITY;
			j->_parent = nullptr;
		}
	}
}

void MapSpaceManager::actualizeTemporaryObstacles (int tankId , bool status)
{
	for (auto& i : Mediator::recieveTanksPosition(tankId))
	{
		if (i != Mediator::getTargetPosition())
		{
			Vector2T<int> pos = i / AssetsStorage::_mapTileDim;
			_nodes[pos._x][pos._y]->_isObstacle = status;
			_nodes[pos._x + 1][pos._y]->_isObstacle = status;
			_nodes[pos._x][pos._y + 1]->_isObstacle = status;
			_nodes[pos._x + 1][pos._y + 1]->_isObstacle = status;
		}
	}
}

void MapSpaceManager::findAreaPos(Node *start , Node* end)
{
	
}

Moves MapSpaceManager::aStar(Node* start, Node* end, int tankId)
{
	//gasete cel mai apropiat punct din aria de
	//acoperire a targetului


	//resetarea tuturor nodurilor
	resetNodes();

	//instiintarea tank-ului curent asupra 
	//poziitilor celorlalte tank-uri
	actualizeTemporaryObstacles(tankId, true);

	//setarea nodului curent
	Node* currentNode = start;
	currentNode->_localGoal = 0.f;
	currentNode->_gloabalGoal = heuristic(start, end);

	//lista = coada
	list<Node*> unvisitedNodes;
	unvisitedNodes.emplace_back(start);

	bool hasPath = true;

	while (!unvisitedNodes.empty() && unvisitedNodes.front() != end  )
	{
		//aici putem face o sortare : list => coada de prioritati
		unvisitedNodes.sort([](const Node* a, const Node* b) {return a->_gloabalGoal < b->_gloabalGoal; });

		//putem avea eroare daca nu avem nimic in lista

		//daca avem obstacole nu le punem
		while (!unvisitedNodes.empty() && (unvisitedNodes.front()->_isVisited || unvisitedNodes.front()->_isObstacle))
		{
			unvisitedNodes.pop_front();
		}

		if (unvisitedNodes.empty())
		{
			break;
		}
		//extragem urmatorul nod din coada => il setam ca vizitat
		currentNode = unvisitedNodes.front();
		currentNode->_isVisited = true;

		for (auto& neighbour : currentNode->_neighbours)
		{
			//putem pun in coada doar un vecin valid
			if (!neighbour->_isVisited)
			{
				// tank-ul nostru este pe 4 tile-uri ->
				//  trebuie avuta in vederea lor
				if (!neighbour->_isObstacle &&
					!_nodes[neighbour->_position._x + 1][neighbour->_position._y]->_isObstacle &&
					!_nodes[neighbour->_position._x][neighbour->_position._y + 1]->_isObstacle &&
					!_nodes[neighbour->_position._x + 1][neighbour->_position._y + 1]->_isObstacle)
					unvisitedNodes.push_back(neighbour);
			}

			//calculam posibila distanta
			float possibleLowerGoal = currentNode->_localGoal + heuristic(currentNode, neighbour);

			//daca este o distanta mai mica facem actualizarea
			if (possibleLowerGoal < neighbour->_localGoal)
			{
				neighbour->_localGoal = possibleLowerGoal;

				neighbour->_parent = currentNode;

				neighbour->_gloabalGoal = neighbour->_localGoal + heuristic(currentNode, end);
			}
		}
	}

	unvisitedNodes.clear();
	// drum cel mai scurt este cel determinat de 
	// parintii tuturor nodurilor incepand cu
	// nodul end


	////resetarea spatiilor ocupate de tank-uri
	actualizeTemporaryObstacles(tankId, false);

	Node* copyPtr = nullptr;
	if (end != nullptr)
	{
		copyPtr = end;
		do {

			//regandeste un pic aici
			if (copyPtr->_parent == nullptr)
			{
				hasPath = false;
				break;
			}
			copyPtr = copyPtr->_parent;
			if (copyPtr->_parent == nullptr)
			{
				hasPath = false;
				break;
			}
		} while (copyPtr->_parent->_parent != nullptr);
	}

	// ne intereseaza doar prima miscare deorece
	// algoritmul ruleaza la fiecare frame
	Moves firstMove = { false , false , false, false };

	if (hasPath)
	{
		if (copyPtr != nullptr)
		{
			if (start->_position._x < copyPtr->_position._x)
			{
				firstMove._right = true;
			}
			if (start->_position._x > copyPtr->_position._x)
			{
				firstMove._left = true;
			}
			if (start->_position._y > copyPtr->_position._y)
			{
				firstMove._up = true;
			}
			if (start->_position._y < copyPtr->_position._y)
			{
				firstMove._down = true;
			}
		}
	}

	return firstMove;
}

void MapSpaceManager::clear()
{
	for (auto& i : _nodes)
	{
		for (auto& j : i)
		{
			delete j;
			j = nullptr;
		}
		i.clear();
	}
}
