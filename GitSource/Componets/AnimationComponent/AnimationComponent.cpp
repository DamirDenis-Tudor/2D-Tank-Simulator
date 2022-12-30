#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(string _type, Vector2T<int> position, float angle, float timer)
	:_position(position), animationSpeed(timer)
{
	TimeManager::createTimer(to_string(_id), animationSpeed);

	/*
		preluam animatia din AssetsStorage
	*/
	_frames = size(AssetsStorage::_effects[_type]);
	for (int i = 0; i < _frames; i++)
	{
		SpriteComponent* sprite = new SpriteComponent(AssetsStorage::_effects[_type][i]);
		_anim.emplace_back(sprite);
		sprite = nullptr;
		_anim[i]->setCameraPosition(position);
		_anim[i]->setAngle(angle);
	}
}

AnimationComponent::~AnimationComponent()
{
	TimeManager::removeTimer(to_string(_id));
	for (auto& i : _anim)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = nullptr;
	}
	_anim.clear();

}

void AnimationComponent::setContinuos()
{
	_isContinuos = true;
}

void AnimationComponent::draw()
{
	_anim[_frameID]->setCameraPosition(_position - CameraManager::offset - _anim[_frameID]->_dest->w / 2);
	_anim[_frameID]->draw();
}

void AnimationComponent::update()
{
	if (!TimeManager::_timers[to_string(_id)]->isTimerWorking())
	{
		_anim[_frameID]->update();
		_frameID++;
		if (_frameID == _frames)
		{
			if (_isContinuos)
			{
				_frameID = 0;
			}
			else
			{
				disable();
			}
		}
		TimeManager::_timers[to_string(_id)]->resetTimer();
	}
}

