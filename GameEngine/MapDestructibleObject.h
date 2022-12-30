#pragma once
#include"SpriteComponent.h"
#include"Mediator.h"
#include"MapSpaceManager.h"
#include"TimeManager.h"

#define Health 10

/*
	Descrierea clasei:
		-> reprezinta totalitatea obiectelor 
		   ce pot fi distruse si reapar dupa un anumit timp
*/
class MapDestructibleObject : public SpriteComponent
{
protected:
	int _type = 0; // id-ul de pe mapa
	Vector2T<int> _mapPos; // faciliteaza comunicarea cu mediatorul
public:
	bool _isBorder = false; // daca face parte din delimitarile mapei
							// va fi un obiect normal
	MapDestructibleObject(SpriteComponent* sprite, Vector2T<int> position);
	~MapDestructibleObject();

	/*
	*	-> dezactiveaza orice modalitate de interactiune cu celelalte obiecte
	*/
	void temporaryDestroyed();
	
	/*
	*  -> reactiveaza modalitatea de interatiune cu celelalte obiecte
	*/
	void respawn();

	void update() override;
};

