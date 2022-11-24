#pragma once

#include"SDL.h"

class TimeManager
{
public:
	static float _reachTime ;
	static float _startTime ;
private:
	//in secunde
	static float _lastFrame ;
	static double _deltaTime ;

	TimeManager()
	{

	}

public:

	static void update() 
	{
		Uint32 currentFrame = SDL_GetTicks();

		currentFrame /= 1000;

		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		updateTimer();
	}

	static float getDeltaTime() 
	{
		return _deltaTime;
	}

	static void setTimer(float time)
	{
		_reachTime = time;
		if (_startTime > time)
		{
			_startTime = 0;
		}
	}

	void resetTimer()
	{
		_startTime = 0;
	}

	bool timerValidStatus()
	{
		if (_startTime < _reachTime)
		{
			return true;
		}

		resetTimer();

		return false; //actiunea s-a finalizat
	}

	static void updateTimer()
	{
		_startTime += _deltaTime;
	}

	static void setDeltatime(double delta)
	{
		_deltaTime = delta;
	}
};
