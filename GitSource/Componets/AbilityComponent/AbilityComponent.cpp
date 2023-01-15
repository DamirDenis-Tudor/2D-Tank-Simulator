#include"AbilityComponent.h"
#include"SoundManager.h"

AbilityComponent::AbilityComponent(string type , SpriteComponent* sprite) : SpriteComponent(sprite) , _name(type)
{
	_isMapObject = true;
}

AbilityComponent::~AbilityComponent()
{
	setSrcTextNullPtr();
}

void AbilityComponent::update()
{
	SpriteComponent::update();

	/*
		vereifcam daca este colectata de un tank
	*/
	int rectDim = 2 * AssetsStorage::_tileDim;
	for (auto& tank : Mediator::getTanksPositions())
	{

		Vector2T<int> rectPos = tank.second ;
		Vector2T<float> floatPos((float)_position._x + AssetsStorage::_tileDim/2, (float)_position._y + AssetsStorage::_tileDim / 2);

		if (CollisionManager::pointCollisionRectagle(floatPos, rectPos, rectDim))
		{
			/*
				in cazul in care tank-ul are o abilitate activa 
				colectarea nu va maia vea loc
			*/
			if (Mediator::hasActiveAbility(tank.first)) return;

			Mediator::addAbility(tank.first, _name);
			if (CameraManager::getFocusId() == tank.first)
			{
				SoundManager::playSoundEfect("ability", 50);
			}
			disable();
		}
	}
}
