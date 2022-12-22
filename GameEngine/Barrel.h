#pragma once
#include"MapDestructibleObject.h"
#include"AnimationsHandler.h"

/*
	Descriere clasa:
		-> suplimentar clasei MapDestructibleObject adauga 
		    animatie de distrugere si damage obiectelor di jurul sau
*/
class Barrel : public MapDestructibleObject
{
private:
	bool explosion = false; // se doreste doar o explozie in timpul in care este disable
public:
	Barrel(SpriteComponent* sprite, Vector2T<int> position);
	void update() override;

};

