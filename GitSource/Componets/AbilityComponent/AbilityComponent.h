#pragma once

#include"SpriteComponent.h"
#include"TimeManager.h"
#include"ColisionManager.h"

/*
	Descriere clasa:
		-> clasa responsabila pentru abilitaile coletabile de pe mapa
*/
class AbilityComponent : public SpriteComponent
{
	friend class SpecialObjectsManager;
private:
	string _name;
	Vector2T<int> _position;
public:
	AbilityComponent(string type , SpriteComponent* spite);
	~AbilityComponent();
	
	void update() override;
};