#pragma once

#include"Component.h"
#include"Bullet.h"
#include"Mine.h"
#include"AnimationsHandler.h"

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

	void update() override;
	void draw() override;

};
