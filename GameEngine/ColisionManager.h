#pragma once

#include"Vector2i.h"
#include"AssetsStorage.h"

/*
	Descriere clasa:
		->implemeteaza utilitare pentru diferite tipuri de collisiuni;
*/
class CollisionManager
{
private:

	CollisionManager() {};

public:
	~CollisionManager() {};
	
	/*
		 ->pentru coliziunea unui obiect verific doar 4 tile-uri
	*/
	static void mapCollision(Vector2T<float>& potentialPos);

	/*
	- calculam cel mai apropiat punct
		de cerc nostru

		- incadram punctul cel mai apropiat
		in spatiul de coliziune al obiectului
		_________________________________
		|				                  |
		point(*) | < -spatiul de coliziune  ->|
		|_______________________________ |

		-calculam un overlap : daca > 0 = > coliziune->recalibare
		->normalizam vectorul
		= > pozitie = pozitie - normVect * overlap
	*/
	static bool circleRectagleCollision(Vector2T<float>& circlePotentialPos, Vector2T<int>& rectaglePos , int& rectagleDim);

	/*
		- verifica coliziunea cu oricare tile din layer-ul cu obiecte colideble
		- indica si pozitia obiectului "lovit" ( de exemplu un bullet loveste zid )
	*/
	static bool pointCollisionMap(Vector2T<float> potentialPos , Vector2T<int> &mapObjectPos);

	/*
		- verifica aparteneta unui punct intr-un rectagle
	*/
	static bool pointCollisionRectagle(Vector2T<float> potentialPos , Vector2T<int> rectPos , int rectDim);

};
