#include"TimeManager.h"

float TimeManager::_deltaTime = 0;
map<string, Timer*> TimeManager::_timers = {};
float Timer::_deltaTime = 0;