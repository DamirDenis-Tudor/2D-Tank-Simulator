#pragma once

#include"SpriteComponent.h"
#include"AssetsStorage.h"
#include"TimeManager.h"

class Animation : public Component
{
private:
	int _frameID = 0;
	int _frames = 0;
	vector<SpriteComponent*> _anim;
	float animationSpeed = 0.5;

public:
	Animation(string _type , Vector2T<int> position)
	{
		TimeManager::createTimer(_id, animationSpeed);
		//_frames = size(AssetsStorage::effects);
		//for (int i = 0; i < _frames ; i++)
		//{
		//	_anim.push_back(new SpriteComponent(AssetsStorage::effects[_type][i] ) )
		//}
	}

	void draw() override
	{
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
};