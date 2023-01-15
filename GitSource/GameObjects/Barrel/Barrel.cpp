#include "Barrel.h"
#include"SoundManager.h"

Barrel::Barrel(SpriteComponent* sprite, Vector2T<int> position) : MapDestructibleObject(sprite, position)
{
}

void Barrel::update()
{
	MapDestructibleObject::update();

	if (!isActive() && !explosion)
	{
		explosion = true;
		AnimationsHandler::addAnimation(new AnimationComponent("barrelDestroy",
			{ _mapPos._x * AssetsStorage::_tileDim + AssetsStorage::_tileDim / 2, _mapPos._y * AssetsStorage::_tileDim - AssetsStorage::_tileDim }, 0));
		SoundManager::playSoundEfect("barrelExplosion" , 30);

		/*
		*  -> in momentul in care un butoi explodeaza
		*	  va aduce damage in jurul lui => pentru fiecare pozitie din jurul lui
		*	  verificam daca avem un obiect inregistrat in clasa Mediator
		*/

		
		// verificare pentru obiectele fixe de pe mapa
		int startCellX = std::max(0, _mapPos._x - 1);
		int endCellX = std::min(AssetsStorage::_layerWidth - 1, _mapPos._x + 1);

		int startCellY = std::max(0, _mapPos._y - 1);
		int endCellY = std::min(AssetsStorage::_layerHeight - 1, _mapPos._y + 1);

		for (int i = startCellX; i <= endCellX; i++)
		{
			for (int j = startCellY; j <= endCellY; j++)
			{
				int id = Mediator::getId({ i , j});
				if (id != -1)
				{
					Mediator::modifyHealth(id, -50);

					/*
					* in cazul in care un obiect distruge alt obiect
					* si acesta la randul lui distruge un tank 
					* punctul va fi inregistrat in dreptul echipei kiler-ului 
					* primului obiect
					*/
					if (Mediator::hasKiller(_id) )
					{
						Mediator::registerKiller(id, Mediator::getKiller(_id));
					}
				}
			}
		}

		// verificare pentru obiectele miscatoare
		for (auto& i : Mediator::getTanksPositions())
		{
			Vector2T<float> floatPos = { (float)i.second._x + AssetsStorage::_tileDim , (float)i.second._y + AssetsStorage::_tileDim };
			Vector2T<int> rectPos = (_mapPos * AssetsStorage::_tileDim + AssetsStorage::_tileDim/2) - 3 * AssetsStorage::_tileDim;
			if (CollisionManager::pointCollisionRectagle(floatPos , rectPos , 6 * AssetsStorage::_tileDim))
			{
				Mediator::modifyHealth(Mediator::getId(i.second), -40);
				/*
				* daca butoiul are un "ucigas" 
				* inseamna ca exista de a inregistra in dreptul 
				* echipei ucigasului un punct
				*/
				if (!Mediator::hasKiller(_id)) return;

				/*
				* totusi daca sunt in aceeiasi echipa
				* a fost un accident..ghinion
				*/
				if (Mediator::checkTeammates(Mediator::getKiller(_id), Mediator::getId(i.second))) return;

				/*
				* daca explozia nu a fost cauzatoare de moarte
				* ...noroc
				*/
				if (Mediator::getHealth(Mediator::getId(i.second)) > 0) return;

				/*
				* inregistram punctul
				*/
				Mediator::addPoint(Mediator::getColorTeam(Mediator::getKiller(_id)));

				/*
				* actualizam tabela
				*/
				InfoManager::setText(Mediator::getColorTeam(Mediator::getKiller(_id)) + "Points",
					to_string(Mediator::getTeamScore(Mediator::getColorTeam(Mediator::getKiller(_id)))));
			}
		}
	}
	else if (isActive())
	{
		explosion = false;
	}
}
