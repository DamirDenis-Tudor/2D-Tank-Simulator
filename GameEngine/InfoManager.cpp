#include "InfoManager.h"

map< string, TextComponent*> InfoManager::_aditionalInfo = {};

InfoManager::InfoManager()
{
}

InfoManager::~InfoManager()
{
	for (auto& info : _aditionalInfo)
	{
		delete info.second;
		info.second = 0;
	}
	_aditionalInfo.clear();
}

void InfoManager::addInfo(string id, TextComponent* info)
{
	if (_aditionalInfo.count(id) != 0)
	{
		delete info;
		info = nullptr;
		return;
	}

	_aditionalInfo.insert(pair<string, TextComponent*>(id, info));
}

void InfoManager::setPosition(string id, Vector2T<int> position)
{
	_aditionalInfo[id]->setPosition(position);
}

void InfoManager::setText(string id, string text)
{
	_aditionalInfo[id]->setText(text);
}

void InfoManager::setColor(string id , SDL_Color color)
{
	_aditionalInfo[id]->_textColor = color;
}

Vector2T<int> InfoManager::getDimension(string id)
{
	return _aditionalInfo[id]->getDimension();
}

void InfoManager::disable(string id)
{
	_aditionalInfo[id]->disable();
}

void InfoManager::enable(string id)
{
	_aditionalInfo[id]->enable();
}

void InfoManager::update()
{
	for (auto& info : _aditionalInfo)
	{
		if (isActive())
		{
			info.second->update();
		}
	}
}

void InfoManager::draw()
{
	for (auto& info : _aditionalInfo)
	{
		if (isActive())
		{
			info.second->draw();
		}
	}
}
