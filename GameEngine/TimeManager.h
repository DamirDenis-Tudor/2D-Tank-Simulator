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
	float _startTime = 0;
	float _reachTime = 0;

public:
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

	int getRemainingTime()
	{
		return static_cast<int>(_reachTime - _startTime);
	}

	static float getDeltaTime()
	{
		return _deltaTime;
	}

	static void setDeltatime(float delta)
	{
		_deltaTime = delta;
	}

	void setLimit(float time)
	{
		_seconds = time;
	}
};

/*
	Descrire clase:
		-> clasa de baza TimeManager are metode ce-i permit sa creeze/elimine timere pe baza unui id
		-> pentru a crea mai multe timere pentru acelasi obiect id-ul este de tip strind

*/
class TimeManager
{
private:
	static float _deltaTime;

	TimeManager() {}
public:
	static map<string, Timer*> _timers;

	static float getDeltaTime()
	{
		return _deltaTime;
	}

	static void setDeltatime(float delta)
	{
		_deltaTime = delta;
	}

	static void createTimer(string id, float seconds)
	{
		_timers.insert(pair<string, Timer*>(id,new Timer(seconds)));
	}

	static void modifyTimer(string id, float seconds)
	{
		_timers[id]->setLimit(seconds);
	}

	static void removeTimer(string id)
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