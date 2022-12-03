#pragma once

#include"Component.h"
#include"Animation.h"
#include"TimeManager.h"

class AnimationsHandler : public Component
{
	static vector<Animation*> _animations;
public:
	AnimationsHandler () {}

	~AnimationsHandler()
	{
		for (auto& i : _animations)
		{
			delete i;
			i = nullptr;
		}
	}

	static void addAnimation(Animation*& animation)
	{
		_animations.emplace_back(animation);
	}

	void update() override
	{
		for (int i = 0; i < _animations.size(); i++)
		{
			_animations[i]->update();
			if (!_animations[i]->isActive())
			{
				TimeManager::removeTimer(_animations[i]->_id);
				
				delete _animations[i];
				_animations[i] = nullptr;
				_animations.erase(_animations.begin() + i);
				i--;
			}
		}
	}

	void draw() override
	{
		for (int i = 0; i < size(_animations); i++)
		{
			_animations[i]->draw();
		}
	}
};

