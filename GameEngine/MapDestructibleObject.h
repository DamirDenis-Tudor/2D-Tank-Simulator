#pragma once
#include"SpriteComponent.h"
#include"Mediator.h"
#include"MapSpaceManager.h"
#include"TimeManager.h"

class MapDestructibleObject : public SpriteComponent
{
protected:
	int _type = 0;
	int _health = 50;
	Vector2T<int> _mapPos;
public:
	bool _isBorder = false;
	MapDestructibleObject(SpriteComponent* sprite, Vector2T<int> position);
	~MapDestructibleObject();

	void temporaryDestroyed();
	void respawn();

	void update() override;
};

