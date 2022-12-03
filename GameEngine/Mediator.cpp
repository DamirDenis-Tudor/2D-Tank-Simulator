#include "Mediator.h"

int Mediator::_targetId = 0;
map<int, Vector2T<int> > Mediator::_tanks = {};
map<  pair<int, int>, Vector2T<int> > Mediator::_bullets = {};