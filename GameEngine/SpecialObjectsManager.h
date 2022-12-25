#pragma once

#include"Component.h"
#include"Bullet.h"
#include"Mine.h"
#include"AnimationsHandler.h"

/*
	Descrierea clasei : 
		-> gestioneaza toate obiecte speciale
		-> permite salvarea lor de oriunde
		-> clasa poate fi instantiata pentru 
		   a putea realiza actualizarea obiectelor
*/
class SpecialObjectsManager : public Component
{
private:
	static vector<Bullet*> _bullets;
	static vector<Mine*> _mines;
public:
	SpecialObjectsManager();
	~SpecialObjectsManager();

	static void addBullet(Bullet *);
	static void addMine(Mine * );

	static int getMinesNumber(int id);

	void update() override;
	void draw() override;

};
