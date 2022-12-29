#pragma once

#include"SpriteComponent.h"
#include"TimeManager.h"
#include"ColisionManager.h"

class AbilityComponent : public SpriteComponent
{
	friend class SpecialObjectsManager;
private:
	string _type;
	Vector2T<int> _position;
public:
	AbilityComponent(string type , SpriteComponent* spite);
	~AbilityComponent();
	
	void update() override;
};