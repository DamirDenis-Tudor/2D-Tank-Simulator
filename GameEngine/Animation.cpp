#include "Animation.h"

Animation::Animation(string _type, Vector2T<int> position, float angle, float timer)
	:_position(position), animationSpeed(timer)
{
	TimeManager::createTimer(_id, animationSpeed);
	_frames = size(AssetsStorage::_effects[_type]);
	for (int i = 0; i < _frames; i++)
	{
		SpriteComponent* sprite = new SpriteComponent(AssetsStorage::_effects[_type][i]);
		_anim.emplace_back(sprite);
		sprite = nullptr;
		_anim[i]->setPosition(position);
		_anim[i]->setAngle(angle);
	}
}

Animation::~Animation()
{
	TimeManager::removeTimer(_id);
	for (auto& i : _anim)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = nullptr;
	}
	_anim.clear();

}

void Animation::setContinuos()
{
	_isContinuos = true;
}

void Animation::draw()
{
	_anim[_frameID]->setPosition(_position - CameraManager::offset - _anim[_frameID]->_dest->w / 2);
	_anim[_frameID]->draw();
}

void Animation::update()
{
	if (!TimeManager::_timers[_id]->isTimerWorking())
	{
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
		TimeManager::_timers[_id]->resetTimer();
	}
}

