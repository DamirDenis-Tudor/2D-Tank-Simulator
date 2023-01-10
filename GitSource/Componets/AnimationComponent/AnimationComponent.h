#pragma once

#include"SpriteComponent.h"
#include"AssetsStorage.h"
#include"TimeManager.h"

/*
	Descrierea clasei:
		
		-> face o copie frame-urilor animatiei din AssetsStorage;
		-> are un timer default de afisare a frame-urilor;
*/
class AnimationComponent : public Component
{
private:
	int _frameID = 0; // frame-ul current
	int _frames = 0; // numarul total de frame-uri
	vector<SpriteComponent*> _anim; //vector de copii al frame-urilor din AssetsStorage
	float animationSpeed = 0;
	Vector2T<int> _position;
	bool _isContinuos = false; // anamiatia poate fi reprezetata permanent

public:
	AnimationComponent(string _type, Vector2T<int> position, float angle , float timer = 0.03);
	~AnimationComponent();

	void setContinuos();

	void draw() override;

	void update() override;
};