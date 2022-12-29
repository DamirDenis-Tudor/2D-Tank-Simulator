#include"AbilityComponent.h"

AbilityComponent::AbilityComponent(string type , SpriteComponent* sprite) : SpriteComponent(sprite) , _type(type)
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

	int rectDim = 2 * AssetsStorage::_tileDim;
	for (auto& tank : Mediator::getTanksPositions())
	{

		Vector2T<int> rectPos = tank.second ;
		Vector2T<float> floatPos((float)_position._x + AssetsStorage::_tileDim/2, (float)_position._y + AssetsStorage::_tileDim / 2);

		if (CollisionManager::pointCollisionRectagle(floatPos, rectPos, rectDim))
		{
			if (Mediator::hasActiveAbility(tank.first)) return;

			Mediator::addAbility(tank.first, _type);
			disable();
		}
	}
}
