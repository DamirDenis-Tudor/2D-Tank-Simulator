#pragma once

#include"Component.h"
#include"Bullet.h"
#include"Mine.h"
#include"AnimationsHandler.h"
#include"AbilityComponent.h"
#include"MapSpaceManager.h"

#define MaxAbilitiesNumber 10

enum Abilities { ShootingBoost=0 , HealthBoost=199 , SpeedBoost = 399};

/*
	Descrierea clasei : 
		-> gestioneaza toate obiecte speciale
		-> permite salvarea lor de oriunde
		-> clasa poate fi instantiata pentru 
		   a putea realiza actualizarea obiectelor
		-> are rolul de a spawna abilitati pe mapa
*/
class SpecialObjectsManager : public Component
{
private:
	static vector<Bullet*> _bullets;
	static vector<Mine*> _mines;
	static vector<AbilityComponent*> _abilities;
public:
	SpecialObjectsManager();
	~SpecialObjectsManager();

	static void addBullet(Bullet *);
	static void addMine(Mine * );
	static int getMinesNumber(int id);

	void spawnAbilities();

	void update() override;
	void draw() override;

};
