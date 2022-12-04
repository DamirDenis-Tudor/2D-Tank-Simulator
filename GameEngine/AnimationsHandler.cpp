#include "AnimationsHandler.h"

vector<Animation*> AnimationsHandler::_animations = {};

AnimationsHandler::~AnimationsHandler()
{
	for (auto& i : _animations)
	{
		delete i;
		i = nullptr;
	}
}

void AnimationsHandler::update()
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

void AnimationsHandler::draw()
{
	for (int i = 0; i < size(_animations); i++)
	{
		_animations[i]->draw();
	}
}

