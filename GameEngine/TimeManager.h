#pragma once

#include"SDL.h"
#include<map>
#include<iostream>
using namespace std;

class Timer
{
private:
	static float _deltaTime;
	float _seconds = 0;

public:
	float _startTime = 0;
	float _reachTime = 0;
	Timer(float seconds) : _seconds(seconds) {}

	Timer() {}

	bool isTimerWorking()
	{
		if (_startTime >= _reachTime)
		{
			_startTime = 0;
			_reachTime = 0;
			return false;
		}
		_startTime += _deltaTime / 1000.f;
		return true;
	}

	void resetTimer()
	{
		_reachTime = _seconds;
		_startTime = 0;
	}

	static float getDeltaTime()
	{
		return _deltaTime;
	}

	static void setDeltatime(float delta)
	{
		_deltaTime = delta;
	}
};

/*
	Descrire clase:
		-> clasa de baza TimeManager are metode ce-i permit sa creeze/elimine timere pe baza unui id

*/
class TimeManager
{
private:
	static float _deltaTime;

	TimeManager() {}
public:
	static map<int, Timer*> _timers;

	static float getDeltaTime()
	{
		return _deltaTime;
	}

	static void setDeltatime(float delta)
	{
		_deltaTime = delta;
	}

	static void createTimer(int& id, float seconds)
	{
		_timers.insert(pair<int, Timer*>(id,new Timer(seconds)));
	}

	static void removeTimer(int& id)
	{
		delete _timers[id];
		_timers[id] = nullptr;
		_timers.erase(id);
	}

	static void clear()
	{
		for(auto &i : _timers)
		{
			delete i.second;
			i.second = nullptr;
		}
		_timers.clear();
	}
};