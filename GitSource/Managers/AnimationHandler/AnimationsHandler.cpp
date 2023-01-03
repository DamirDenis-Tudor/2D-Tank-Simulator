#include "AnimationsHandler.h"

vector<AnimationComponent*> AnimationsHandler::_animations = {};

AnimationsHandler::~AnimationsHandler()
{
	for (auto& i : _animations)
	{
		delete i;
		i = nullptr;
	}
	_animations.clear();
}

void AnimationsHandler::update()
{
	for (int i = 0; i < _animations.size(); i++)
	{
		_animations[i]->update();
		/*
			daca o animatia s-a terminat este eliminata
		*/
		if (!_animations[i]->isActive())
		{
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

