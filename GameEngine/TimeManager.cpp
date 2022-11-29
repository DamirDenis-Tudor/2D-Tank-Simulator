#include"TimeManager.h"

float TimeManager::_deltaTime = 0;
map<int, Timer*> TimeManager::_timers = {};
float Timer::_deltaTime = 0;