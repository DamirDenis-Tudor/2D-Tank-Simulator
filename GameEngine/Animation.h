#pragma once

#include"SpriteComponent.h"
#include"AssetsStorage.h"
#include"TimeManager.h"

/*
	Descrierea clasei:
		
		-> face o copie frame-urilor animatiei din AssetsStorage;
		-> are un timer default de afisare a frame-urilor;

		!NOTA: Animatia este relativa la camera => actualizarea 
			   la fiecare desenare a pozitie, astfel daca player-ul se 
			   misca animatia "ramane pe loc" cum este firesc;
*/

//animation manager va avea un vector de componente

class Animation : public Component
{
private:
	int _frameID = 0;
	int _frames = 0;
	vector<SpriteComponent*> _anim;
	float animationSpeed = 0.03;
	Vector2T<int> _position;

public:
	Animation(string _type , Vector2T<int> position , float angle):_position(position)
	{
		TimeManager::createTimer(_id, animationSpeed);
		_frames = size(AssetsStorage::_effects[_type]);
		for (int i = 0; i < _frames ; i++)
		{
			SpriteComponent* sprite = new SpriteComponent(AssetsStorage::_effects[_type][i]);
			_anim.push_back(sprite);
			sprite = nullptr;
			_anim[i]->setPosition(position);
			_anim[i]->setAngle(angle);
		}
	}

	void draw() override
	{
		_anim[_frameID]->setPosition(_position - CameraManager::offset - _anim[_frameID]->_dest->w/2);
		_anim[_frameID]->draw();
	}

	void update() override
	{
		if (!TimeManager::_timers[_id]->isTimerWorking())
		{
			_frameID++;
			if (_frameID == _frames)
			{
				disable();
			}
			TimeManager::_timers[_id]->resetTimer();
		}
	}

	void clear() override
	{
		TimeManager::removeTimer(_id);

		for (int i = 0; i < _anim.size(); i++)
		{
			_anim[i]->clear();
			delete _anim[i];
			_anim[i] = nullptr;
			_anim.erase(_anim.begin() + i);
			i--;
		}
		_anim.clear();
	}
};