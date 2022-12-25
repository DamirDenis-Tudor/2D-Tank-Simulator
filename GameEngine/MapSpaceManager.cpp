#include"MapSpaceManager.h"

int MapSpaceManager::_range = 5;
int MapSpaceManager::_curretTankId = 0;
string MapSpaceManager::_currentColor = "";
vector<vector<Node*>> MapSpaceManager::_nodes = {};
Node* MapSpaceManager::_pastEndPos = nullptr;
void MapSpaceManager::setUser(int id, string color)
{
	_curretTankId = id;
	_currentColor = color;
}

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
				node->_isPermanent = true;
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

			////vecinii pe diagonala
			if (i > 0 && j > 0)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i - 1][j - 1]);
			}
			if (i > 0 && j < AssetsStorage::_layerHeight - 1)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i - 1][j + 1]);
			}
			if (j > 0 && i < AssetsStorage::_layerWidth - 1)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i + 1][j - 1]);
			}
			if (i < AssetsStorage::_layerHeight - 1 && j < AssetsStorage::_layerHeight - 1)
			{
				_nodes[i][j]->_neighbours.push_back(_nodes[i + 1][j + 1]);
			}
		}
	}
}

void MapSpaceManager::printMap()
{
	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (!_nodes[j][i]->_isPermanent)
			{
				std::cout << _nodes[j][i]->_isObstacle << " ";
			}
			else
			{
				std::cout << 0 << " ";
			}
		}
		std::cout << "\n";
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

bool MapSpaceManager::nodeContainsTemporaryObstacles(Node* node)
{
	bool intersect = false;
	actualizeTemporaryObstacles(true);
	if (node->_isObstacle)
	{
		intersect = true;
	}
	actualizeTemporaryObstacles(false);
	return intersect;
}

bool MapSpaceManager::bodyContainsObstacles(Node* body)
{
	if (_nodes[body->_position._x][body->_position._y]->_isObstacle ||
		_nodes[body->_position._x][body->_position._y + 1]->_isObstacle ||
		_nodes[body->_position._x + 1][body->_position._y]->_isObstacle ||
		_nodes[body->_position._x + 1][body->_position._y + 1]->_isObstacle)
	{
		return true;
	}
	return false;
}

Vector2T<int> MapSpaceManager::getSpawnPosition()
{
	actualizeTemporaryObstacles(true);

	Vector2T<int> position;
	do {
		position._x = rand() % (SpawnRange - 1) + Mediator::getSpawnZone(_currentColor)._x;
		position._y = rand() % (SpawnRange - 1) + Mediator::getSpawnZone(_currentColor)._y;

	} while (bodyContainsObstacles(getNode(position)));

	actualizeTemporaryObstacles(false);

	return position * AssetsStorage::_tileDim;
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

bool MapSpaceManager::simulateBulletTrajectory(Vector2T<int> shotter)
{
	shotter *= AssetsStorage::_tileDim;

	Node* a = nodeConversion(Mediator::getNearestEnemyPosition(_curretTankId, _currentColor));

	Vector2T<int> target = a->_position * AssetsStorage::_tileDim;

	// atat pentru shotter cat si pentru target, scalam pozitiile 
	// relative la eram (din pozitia pe map in pozitia pe eran)
	// acest lucru ajuta la o simulare mai buna
	Vector2T<float> scaledShotter = Vector2T<float>{ (float)(shotter._x) , (float)(shotter._y) };
	Vector2T<float> scaledTarget = Vector2T<float>{ (float)(target._x) ,(float)(target._y) };

	float angle = (SDL_atan2((double)(scaledShotter._y - scaledTarget._y), (double)(scaledShotter._x - scaledTarget._x)) * 180 / M_PI);
	float sin = SDL_sin((angle)*M_PI / 180);
	float cos = SDL_cos((angle)*M_PI / 180);

	while (true)
	{
		scaledShotter._x -= SDL_cos((angle)*M_PI / 180) * AssetsStorage::_tileDim / 2.f;
		scaledShotter._y -= SDL_sin((angle)*M_PI / 180) * AssetsStorage::_tileDim / 2.f;

		// daca bullet-ul loveste targetul 
		// oprim simularea si returnam true
		if (CollisionManager::pointCollisionRectagle(scaledShotter + AssetsStorage::_tileDim, target, 2 * AssetsStorage::_tileDim))
		{
			break;
		}

		// daca bullet-ul nu are intersectie cu
		// body-ul shootter-ului putem face verificarea 
		// daca are coliziune cu alte obstacole
		if (!(CollisionManager::pointCollisionRectagle(scaledShotter + AssetsStorage::_tileDim, shotter, 2 * AssetsStorage::_tileDim)))
		{
			Vector2T<float> pos = (scaledShotter + AssetsStorage::_tileDim) / AssetsStorage::_tileDim;

			if (_nodes[pos._x][pos._y]->_isObstacle)
			{
				return false;
			}
		}
	}

	return true;
}

void MapSpaceManager::checkNearestNodeInRange(Node* start, Node*& end)
{
	// stabilim zona de cautare a pozitie
	// acesta va fi pe conturul matricei determinate
	int startCellX = std::max(1, (end->_position._x - _range));
	int endCellX = std::min(AssetsStorage::_layerWidth - 2, (end->_position._x + _range + 1));
	int startCellY = std::max(1, (end->_position._y - _range));
	int endCellY = std::min(AssetsStorage::_layerHeight - 2, (end->_position._y + _range + 1));

	float lowestDistance = INFINITY;

	// in caz de nu gasim o pozitie 
	// ne rezumam la ultima pozitie gasita
	// si daca nu vom aveam cale, tank-ul va astepta (hasPath = false)
	Node* nearestNode = _pastEndPos;

	for (int i = startCellX; i <= endCellX; i++)
	{
		for (int j = startCellY; j <= endCellY; j++)
		{
			// verificam conturul range-ului
			if (i == startCellX || i == endCellX || j == startCellY || j == endCellY)
			{
				//calculam distanta pana la distanta de pe conturul matricei
				float distance = Distances::eucliadianDistance(start->_position, _nodes[i][j]->_position);

				// daca gasim o pozitie in range mai apropiata 
				// verificam daca corpul tank-ului nu va avea 
				// vreo coliziune in zona respectiva
				if (distance < lowestDistance && !bodyContainsObstacles(_nodes[i][j]))
				{
					// pentru a valida pozitia trebuie 
					// sa verificam daca avem posibiliatea de tragere
					if (simulateBulletTrajectory(_nodes[i][j]->_position))
					{
						lowestDistance = distance;
						nearestNode = _nodes[i][j];
					}
				}
			}
		}

		end = nearestNode;
		_pastEndPos = end;
	}

}

void MapSpaceManager::actualizeTemporaryObstacles(bool status) //varibila idEnd este temporara
{
	for (auto& i : Mediator::recieveTanksPositions(_curretTankId))
	{
		Node* a = nodeConversion(i);

		if (!_nodes[a->_position._x][a->_position._y]->_isPermanent)
		{
			_nodes[a->_position._x][a->_position._y]->_isObstacle = status;
		}
		if (!_nodes[a->_position._x + 1][a->_position._y]->_isPermanent)
		{
			_nodes[a->_position._x + 1][a->_position._y]->_isObstacle = status;
		}
		if (!_nodes[a->_position._x][a->_position._y + 1]->_isPermanent)
		{
			_nodes[a->_position._x][a->_position._y + 1]->_isObstacle = status;
		}
		if (!_nodes[a->_position._x + 1][a->_position._y + 1]->_isPermanent)
		{
			_nodes[a->_position._x + 1][a->_position._y + 1]->_isObstacle = status;
		}
	}
}

Node*& MapSpaceManager::nodeConversion(Vector2T<int> position)
{
	Vector2T<float> floatPos = { (float)position._x / (float)AssetsStorage::_tileDim  , (float)position._y / (float)AssetsStorage::_tileDim };
	position /= AssetsStorage::_tileDim;
	if (floatPos._x - position._x >= 0.75)
	{
		position._x += 1;
	}
	if (floatPos._y - position._y >= 0.75)
	{
		position._y += 1;
	}
	return _nodes[position._x][position._y];
}

bool MapSpaceManager::isInRangeOfTarget(Node* start)
{

	if (CollisionManager::pointCollisionRectagle({ (float)start->_position._x * AssetsStorage::_tileDim  , (float)start->_position._y * AssetsStorage::_tileDim },
		Mediator::getNearestEnemyPosition(_curretTankId, _currentColor) - (2 * _range) * AssetsStorage::_tileDim,
		2 * (2 * _range) * AssetsStorage::_tileDim))
	{
		return true;
	}
	return false;
}

Moves MapSpaceManager::aStar(Vector2T<int> startPos, Vector2T<int> endPos)
{
	//initial conversion
	Node* start = nodeConversion(startPos);
	Node* end = nodeConversion(endPos);

	//resetarea tuturor nodurilor
	resetNodes();

	//actualizarea pozitiilor tank-urilor
	actualizeTemporaryObstacles(true);

	//cautam cea mai optimala poztie in range-ul tank-ului inamic
	checkNearestNodeInRange(start, end);

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
				if (!bodyContainsObstacles(neighbour))
				{
					unvisitedNodes.push_back(neighbour);
				}
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
	Moves firstMove = { false , false , false, false , false , false };
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


	if (simulateBulletTrajectory(start->_position))
	{
		// daca este in range, indiferent de obstacolul din fata 
		// va trage si obstacolul va fi distrus

		// daca nu este in range se verifica posibilitatea de tragere
		firstMove._shoting = true;
	}
	else if (isInRangeOfTarget(start))
	{
		// daca nu este in range se verifica posibilitatea de tragere
		firstMove._shoting = true;
	}

	////resetarea spatiilor ocupate de tank-uri
	actualizeTemporaryObstacles(false);

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
