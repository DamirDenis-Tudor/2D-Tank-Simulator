#pragma once
#include"SpriteComponent.h"
#include"Mediator.h"

class Wall : public SpriteComponent
{
	int health = 100;
	Vector2T<int> _mapPos;
public:
	Wall(SpriteComponent* sprite, Vector2T<int> position);
	~Wall();

	void update() override;
};

