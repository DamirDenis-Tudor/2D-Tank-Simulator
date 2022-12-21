#pragma once
#include"MapDestructibleObject.h"
#include"AnimationsHandler.h"

class Barrel : public MapDestructibleObject
{
private:
	bool explosion = false;
public:
	Barrel(SpriteComponent* sprite, Vector2T<int> position);
	void update() override;

};

