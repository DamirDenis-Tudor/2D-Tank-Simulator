
#include "Mine.h"

Mine::Mine(string type, Vector2T<int> position , int tankId) : _position(position) , _tankId(tankId)
{
	_idle = new Animation(type , position , 0 , 0.05 );
	_idle->setContinuos(); // setam animatia continua

	TimeManager::createTimer(_id , 30);
	TimeManager::_timers[_id]->resetTimer();
}

Mine::~Mine()
{
	delete _idle;
	_idle = nullptr;
	TimeManager::removeTimer(_id);
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
			Node: daca nu se verifica a doua condtitie posesorul daca moare
				  si mai are mine active, nu va mai fi vizibil in mediator
				  astfel minele vor fi activare de tank-urile prietene
		*/
		if (!Mediator::checkTeammates(_tankId, Mediator::getId(i)) 
			&& Mediator::stillExist(_tankId) )
		{
			if (CollisionManager::pointCollisionRectagle(floatPos, rectPos, rectDim))
			{
				hasCollision = true;
				Mediator::registerHit(Mediator::getId(i), 50);
			}
		}
	}

	/*
		-> mina este dezactivata dupa un anumit timp
	*/
	if (!TimeManager::_timers[_id]->isTimerWorking() || hasCollision)
	{
		disable();
	}
}
