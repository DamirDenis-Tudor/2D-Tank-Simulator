#include"MapSpaceManager.h"

vector<vector<Node*>> MapSpaceManager::_nodes = {};
Node* MapSpaceManager::_pastEndPos = nullptr;

void MapSpaceManager::initNodes()
{
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

	//for (int i = 0; i < AssetsStorage::_layerWidth; i++)
	//{
	//	for (int j = 0; j < AssetsStorage::_layerHeight; j++)
	//	{
	//		if (AssetsStorage::_mapLayers["colidble"][j][i] != 0 || 
	//			AssetsStorage::_mapLayers["colidble"][j+1][i] != 0 ||
	//			AssetsStorage::_mapLayers["colidble"][j][i+1] != 0 || 
	//			AssetsStorage::_mapLayers["colidble"][j+1][i+1] != 0 )
	//		{
	//			_nodes[i][j]->_isObstacle = true;
	//		}
	//	}
	//}

	for (int i = 0; i < AssetsStorage::_layerWidth; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerHeight; j++)
		{
			//nodurile sus jos stanga dreapta
			if (j > 0 && !_nodes[i][j - 1]->_isObstacle)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i][j - 1]);
			}
			if (j < AssetsStorage::_layerHeight - 1 && !_nodes[i][j + 1]->_isObstacle)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i][j + 1]);
			}
			if (i > 0 && !_nodes[i-1][j]->_isObstacle)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i - 1][j]);
			}
			if (i < AssetsStorage::_layerWidth - 1 && !_nodes[i+1][j]->_isObstacle)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i + 1][j]);
			}

			//vecinii pe diagonala
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

float MapSpaceManager::heuristic(Node* a, Node* b)
{
	return Distances::eucliadianDistance(a->_position, b->_position);
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

bool MapSpaceManager::simulateBulletTrajectory(Vector2T<int> shotter, Vector2T<int>target)
{
	float xT = target._x;
	float yT = target._y;
	shotter *= AssetsStorage::_mapTileDim;
	target *= AssetsStorage::_mapTileDim;

	Vector2T<float> scaledShotter = Vector2T<float>{ (float)(shotter._x + AssetsStorage::_mapTileDim/2 ) , (float)(shotter._y + AssetsStorage::_mapTileDim/2 ) } ;
	Vector2T<float> scaledTarget = Vector2T<float>{ (float)(target._x + AssetsStorage::_mapTileDim/2) ,(float)(target._y + AssetsStorage::_mapTileDim/2) };

	float angle = (SDL_atan2((double)(scaledShotter._y - scaledTarget._y), (double)(scaledShotter._x - scaledTarget._x)) * 180 / M_PI);

	float cos = SDL_cos((angle)*M_PI / 180);
	float sin = SDL_sin((angle)*M_PI / 180);
	
	while (true)
	{
		scaledShotter._x -= cos * (float)AssetsStorage::_mapTileDim/8.f;
		scaledShotter._y -= sin * (float)AssetsStorage::_mapTileDim/8.f;

		if (scaledShotter._x >= scaledTarget._x - AssetsStorage::_mapTileDim / 2 && scaledShotter._x <= (float)(scaledTarget._x + AssetsStorage::_mapTileDim/2) &&
			scaledShotter._y >= scaledTarget._y - AssetsStorage::_mapTileDim / 2 && scaledShotter._y <= (float)(scaledTarget._y + AssetsStorage::_mapTileDim/2))
		{
			break;
		}

		float y = (scaledShotter._y ) / (float)AssetsStorage::_mapTileDim ;
		float x = (scaledShotter._x ) / (float)AssetsStorage::_mapTileDim;

		if (!(scaledShotter._x >= shotter._x && scaledShotter._x <= shotter._x + AssetsStorage::_mapTileDim &&
			scaledShotter._y >= shotter._y && scaledShotter._y <= shotter._y + AssetsStorage::_mapTileDim))
		{
			if (AssetsStorage::_mapLayers["colidble"][y][x] != 0 &&
				_nodes[x][y] != _nodes[xT ][yT] &&
				_nodes[x][y] != _nodes[xT+1][yT] &&
				_nodes[x][y] != _nodes[xT][yT+1] &&
				_nodes[x][y] != _nodes[xT+1][yT+1])
			{
				return false;
			}
		}

	}

	return true;
}

void MapSpaceManager::checkNearestNodeInRange(int tankId, Node* start, Node*& end, int range)
{
	// stabilim zona de cautare a pozitie
	// acesta va fi pe conturul matricei determinate
	int startCellX = std::max(1, (end->_position._x - range));
	int endCellX = std::min(AssetsStorage::_layerWidth - 2, (end->_position._x + range));
	int startCellY = std::max(1, (end->_position._y - range));
	int endCellY = std::min(AssetsStorage::_layerHeight - 2, (end->_position._y + range));

	float lowestDistance = INFINITY;
	
	// in caz de nu gasim o pozitie 
	// ne rezumam la ultima pozitie gasita
	// si daca nu vom aveam cale, tank-ul va astepta (hasPath = false)
	Node* nearestNode = _pastEndPos;

	for (int i = startCellX; i <= endCellX; i++)
	{
		for (int j = startCellY; j <= endCellY; j++)
		{
			if (i == startCellX || i == endCellX  || j == startCellY || j == endCellY )
			{
				//calculam distanta pana la distanta de pe conturul matricei
				float distance = Distances::eucliadianDistance(start->_position, _nodes[i][j]->_position);

				//daca este mai mica actualizam lowestDistance si nearestNode
				if (distance < lowestDistance && 
					!_nodes[i][j]->_isObstacle&&
					!_nodes[i][j+1]->_isObstacle&&
					!_nodes[i+1][j]->_isObstacle&&
					!_nodes[i+1][j+1]->_isObstacle)
				{
					// pentru a valida pozitia trebuie sa verificam daca avem posibiliatea de tragere
					if (simulateBulletTrajectory(_nodes[i][j]->_position, end->_position))
					{
						lowestDistance = distance;
						nearestNode = _nodes[i][j];
					}
				}
			}
		}
	}

	end = nearestNode;
	_pastEndPos = end;
}

void MapSpaceManager::actualizeTemporaryObstacles(int tankId, bool status) //varibila idEnd este temporara
{
	for (auto& i : Mediator::recieveTanksPosition(tankId))
	{
			Vector2T<int> pos = i / AssetsStorage::_mapTileDim;
			_nodes[pos._x][pos._y]->_isObstacle = status;
			_nodes[pos._x + 1][pos._y]->_isObstacle = status;
			_nodes[pos._x][pos._y + 1]->_isObstacle = status;
			_nodes[pos._x + 1][pos._y + 1]->_isObstacle = status;
	}
}

Moves MapSpaceManager::aStar(Node* start, Node* end, int tankId)
{
	//resetarea tuturor nodurilor
	resetNodes();

	//actualizarea pozitiilor tank-urilor
	actualizeTemporaryObstacles(tankId, true);

	//facem o copie catre tinta noastra
	//pentru ca va fi modificata de apelul urmatoarei functii
	Node* target = end;
	checkNearestNodeInRange(tankId, start, end);

	//setarea nodului curent
	Node* currentNode = start;
	currentNode->_localGoal = 0.f;
	currentNode->_gloabalGoal = heuristic(start, end);

	//lista = coada
	list<Node*> unvisitedNodes;
	unvisitedNodes.emplace_back(start);

	bool hasPath = true;

	while (!unvisitedNodes.empty() && unvisitedNodes.front() != end)
	{

		//aici putem face o sortare : list => coada de prioritati
		// este comentata pentru ca reduce performata => tank-uri nu mai sunt asa de "try hard"
		
		//unvisitedNodes.sort([](const Node* a, const Node* b) {return a->_gloabalGoal < b->_gloabalGoal; });

		//scoatem nodurile vizitate
		while (!unvisitedNodes.empty() && unvisitedNodes.front()->_isVisited)
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
				// trebuie verificate toate cele 4 tile-uri ale tak-ului
				if (!neighbour->_isObstacle &&
					!_nodes[neighbour->_position._x + 1][neighbour->_position._y]->_isObstacle &&
					!_nodes[neighbour->_position._x][neighbour->_position._y + 1]->_isObstacle &&
					!_nodes[neighbour->_position._x + 1][neighbour->_position._y + 1]->_isObstacle)
				{
					unvisitedNodes.push_back(neighbour);


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
		}
	}

	////resetarea spatiilor ocupate de tank-uri
	actualizeTemporaryObstacles(tankId, false);

	unvisitedNodes.clear();

	// cautam prima mutare in drumul gasit
	// daca ajungem la nodul care are parinte nodul start, mutarea este gasita
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

	//daca am gasit un drum valid ne intereseaza prima mutare
	Moves firstMove = { false , false , false, false , false };
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
	
	//verificam daca avem posibilitatea de tragere
	if (simulateBulletTrajectory(start->_position, target->_position ))
	{
		firstMove._shoting = true;
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
