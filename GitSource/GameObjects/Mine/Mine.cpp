
#include "Mine.h"
#include"SoundManager.h"

Mine::Mine(string type, Vector2T<int> position , int tankId) : AnimationComponent(type, position, 0, 0.05) , _name(type), _tankId(tankId)
{
	setContinuos(); // setam animatia continua

	TimeManager::createTimer(to_string(_id) + "detonation", 15);
	TimeManager::getTimer(to_string(_id) + "detonation")->resetTimer();
}

Mine::~Mine()
{
	TimeManager::removeTimer(to_string(_id) + "detonation");
}

void Mine::update()
{
	AnimationComponent::update();

	/*
		-> se veririfica in range-ul minei daca
		   exista un tank : daca da se activeaza
	*/
	bool hasCollision = false;
	int rectDim = 4 * AssetsStorage::_tileDim;
	for (auto& i : Mediator::recieveTanksPositions(_tankId))
	{
		Vector2T<int> rectPos = i - AssetsStorage::_tileDim;
		Vector2T<float> floatPos((float)getPosition()._x, (float)getPosition()._y );
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
				/*
				* daca este activata => damage
				*/
				Mediator::modifyHealth(Mediator::getId(i), -35);
				if (Mediator::getHealth(Mediator::getId(i)) <= 0)
				{
					/*
					* daca a cauzat moartea inamicului
					* se inregistreaza in punctul
					*/
					Mediator::addPoint(Mediator::getColorTeam(_tankId));

					/*
					* se actualizeaza tabela
					*/
					InfoManager::setText(Mediator::getColorTeam(_tankId) + "Points",
						to_string(Mediator::getTeamScore(Mediator::getColorTeam(_tankId))));
				}
			}
		}
	}

	/*
		-> mina este dezactivata dupa un anumit timp
	*/
	if (!TimeManager::getTimer(to_string(_id) + "detonation")->isTimerWorking() || hasCollision)
	{
		disable();
	
		if (isOnCamera())
		{
			SoundManager::playSoundEfect("mineExplosion", 20);
		}

		/*
			-> se verifica coliziunile cu obiectele de pe mapa in momentul in care mina explodeaza
		*/
		Vector2T<int> mapPos = getPosition() / AssetsStorage::_tileDim;

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
					/*
					* in cazul in care a distrus un obiectsi
					* acesta la randul lui distruge un tank,
					* echipa celui care a distrus tank-ul va primi un punct
					*/
					Mediator::modifyHealth(id, -35);
					Mediator::registerKiller(id , _tankId);
				}
			}
		}
	}
}
