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

void Director::setBuilderAttributes(const char* type, const char* color, Vector2T<int> position )
{
	_builder->setAtrributes(type, color, position);
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
