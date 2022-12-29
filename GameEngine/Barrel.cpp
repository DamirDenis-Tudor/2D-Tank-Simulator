#include "Barrel.h"

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
					Mediator::modifyHealth(id, -100);
				}
			}
		}

		// verificare pentru obiectele miscatoare
		for (auto& i : Mediator::getTanksPositions())
		{
			Vector2T<float> floatPos = { (float)i.second._x + AssetsStorage::_tileDim , (float)i.second._y + AssetsStorage::_tileDim };
			Vector2T<int> rectPos = _mapPos * AssetsStorage::_tileDim - 3 * AssetsStorage::_tileDim;
			if (CollisionManager::pointCollisionRectagle(floatPos , rectPos , 6 * AssetsStorage::_tileDim))
			{
				Mediator::modifyHealth(Mediator::getId(i.second), -50);

				if (!Mediator::hasKiller(_id)) return;

				if (Mediator::checkTeammates(Mediator::getKiller(_id), Mediator::getId(i.second))) return;

				Mediator::addPoint(Mediator::getColorTeam(Mediator::getKiller(_id)));

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
