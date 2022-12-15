#include "Wall.h"

Wall::Wall(SpriteComponent* sprite, Vector2T<int> position) :SpriteComponent(sprite), _mapPos(position)
{
	Mediator::registerWall(_id, _mapPos);
}

Wall::~Wall()
{
}

void Wall::update()
{
	SpriteComponent::update();
	health = health - Mediator::checkForDamage(_id);
	if (health < 0)
	{
		health = 0;
		disable();
	}
}

