#pragma once
#include"SpriteComponent.h"
#include"Mediator.h"
#include"MapSpaceManager.h"
#include"TimeManager.h"

class Wall : public SpriteComponent
{
	int _wallType = 0;
	int _health = 50;
	Vector2T<int> _mapPos;
public:
	bool _isBorder = false;
	Wall(SpriteComponent* sprite, Vector2T<int> position);
	~Wall();

	void temporaryDestroyed();
	void respawn();

	void update() override;
};

