#include "Director.h"

Builder* Director::_builder = nullptr;

void Director::setBuilder(Builder * builder)
{
	if (_builder != nullptr)
	{
		delete _builder;
		_builder = nullptr;
	}
	_builder = builder;
}

void Director::setBuilderAttributes(string type, string color)
{
	_builder->setAtrributes(type, color);
}

Component* Director::getResult()
{
	_builder->build();
	return _builder->_result;
}

void Director::clear()
{
	delete _builder;
}
