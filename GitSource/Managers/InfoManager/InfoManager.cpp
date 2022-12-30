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

void InfoManager::setCameraPosition(string id, Vector2T<int> position)
{
	if (_aditionalInfo.count(id) == 0) return;

	_aditionalInfo[id]->setCameraPosition(position);
}

void InfoManager::setText(string id, string text)
{
	if (_aditionalInfo.count(id) == 0) return;

	_aditionalInfo[id]->setText(text);
}

void InfoManager::setColor(string id, SDL_Color color)
{
	if (_aditionalInfo.count(id) == 0) return;

	_aditionalInfo[id]->_textColor = color;
}

Vector2T<int> InfoManager::getDimension(string id)
{
	if (_aditionalInfo.count(id) == 0) return { -1,-1 };

	return _aditionalInfo[id]->getDimension();
}

void InfoManager::disable(string id)
{
	if (_aditionalInfo.count(id) == 0) return;

	_aditionalInfo[id]->disable();
}

void InfoManager::enable(string id)
{
	if (_aditionalInfo.count(id) == 0) return;

	_aditionalInfo[id]->enable();
}

void InfoManager::update()
{
	for (auto& info : _aditionalInfo)
	{
		info.second->update();
	}
}

void InfoManager::draw()
{
	for (auto& info : _aditionalInfo)
	{
		info.second->draw();
	}
}
