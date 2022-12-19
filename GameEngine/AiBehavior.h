#pragma once
#include "Behavior.h"


/*
	Descriere clasa:

		-> implementeaza logica unui Ai ;
			- localizeaza cel mai apropiat inamic si folosind un 
			algorithm de path finding implementat in MapSpaceManager 
			primeste o miscare de executat (miscare intr-o directie sau tragere)
*/
class AiBehavior : public Behavior
{
	bool _isActivated = true;

public:

	void patrol();

	void follow();

	void BrainAi();

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override;
};

