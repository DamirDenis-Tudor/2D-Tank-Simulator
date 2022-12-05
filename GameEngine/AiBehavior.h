#pragma once
#include "Behavior.h"


/*
	Descriere clasa:

		->
*/

/*
	todo:
		-> implementare A*
		-> implementarea unei cozi cu miscari optimale pe baza algoritmului
		   ex: _down , _left , _left , _left
*/

class AiBehavior : public Behavior
{
	Vector2T<int> _nextPos;
	bool _isActivated = false;

public:

	void patrol();

	void follow();

	void BrainAi();

	void SyncMoves();

	void movement(Vector2T<int>& position, Vector2T<float> velocity) override;
};

