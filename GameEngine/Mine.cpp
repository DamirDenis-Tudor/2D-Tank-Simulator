
#include "Mine.h"

Mine::Mine(string type, Vector2T<int> position , int tankId) : _type(type), _position(position), _tankId(tankId)
{
	_idle = new AnimationComponent(type , position , 0 , 0.05 );
	_idle->setContinuos(); // setam animatia continua

	TimeManager::createTimer(to_string(_id), 15);
	TimeManager::_timers[to_string(_id)]->resetTimer();
}

Mine::~Mine()
{
	delete _idle;
	_idle = nullptr;
	TimeManager::removeTimer(to_string(_id));
}

void Mine::draw()
{
	_idle->draw();
}

void Mine::update()
{
	_idle->update();


	/*
		-> se veririfica in range-ul minei daca
		   exista un tank : daca da se activeaza
	*/
	bool hasCollision = false;
	int rectDim = 4 * AssetsStorage::_tileDim;
	for (auto& i : Mediator::recieveTanksPositions(_tankId))
	{
		Vector2T<int> rectPos = i - AssetsStorage::_tileDim;
		Vector2T<float> floatPos((float)_position._x, (float)_position._y );
		/*
			-> se verifica daca posesorul minei si tank-ul 
			   sunt in aceeasi echipa si daca posesorul exista

			Node: daca nu se verifica a doua condtitie, posesorul daca moare
				  si mai are mine active, nu va mai fi vizibil in mediator
				  astfel minele vor fi activate de tank-urile prietene
		*/
		if ((!Mediator::checkTeammates(_tankId, Mediator::getId(i)) ))
		{
			if (CollisionManager::pointCollisionRectagle(floatPos, rectPos, rectDim))
			{
				hasCollision = true;
				Mediator::modifyHealth(Mediator::getId(i), -25);
				if (Mediator::getHealth(Mediator::getId(i)) <= 0)
				{
					Mediator::addPoint(Mediator::getColorTeam(_tankId));
					InfoManager::setText(Mediator::getColorTeam(_tankId) + "Points",
						to_string(Mediator::getTeamScore(Mediator::getColorTeam(_tankId))));
				}
			}
		}
	}

	/*
		-> mina este dezactivata dupa un anumit timp
	*/
	if (!TimeManager::_timers[to_string(_id)]->isTimerWorking() || hasCollision)
	{
		disable();
	
		/*
			-> se verifica coliziunile cu obiectele de pe mapa in momentul in care mina explodeaza
		*/
		Vector2T<int> mapPos = _position / AssetsStorage::_tileDim ;

		int startCellX = std::max(0, mapPos._x - 2);
		int endCellX = std::min(AssetsStorage::_layerWidth - 2, mapPos._x + 2);

		int startCellY = std::max(0, mapPos._y - 2);
		int endCellY = std::min(AssetsStorage::_layerHeight - 2, mapPos._y + 2);

		for (int i = startCellX; i <= endCellX; i++)
		{
			for (int j = startCellY; j <= endCellY; j++)
			{
				int id = Mediator::getId({ i , j });
				if (id != -1)
				{
					Mediator::modifyHealth(id, -100);
				}
			}
		}
	}
}
