#include"Map.h"


Map::Map()
{
	init();
}

Map::~Map()
{
	for (auto& i : _drawbles)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = 0;
	}
	_drawbles.clear();
}

void Map::init()
{
	resetCouter();
	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["ground"][i][j] != 0)
			{
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_tiles[AssetsStorage::_mapLayers["ground"][i][j] - 1]);
				tile->setPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
				tile->_isTile = true;
				_drawbles.push_back(tile);

				tile = nullptr;
			}
		}
	}

	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["decor"][i][j] != 0)
			{
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_tiles[AssetsStorage::_mapLayers["decor"][i][j] - 1]);
				tile->setPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
				tile->_isTile = true;
				_drawbles.push_back(tile);
				tile = nullptr;
			}
		}
	}

	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				Wall* wall = new Wall(AssetsStorage::_tiles[AssetsStorage::_mapLayers["colidble"][i][j] - 1], Vector2T<int>(j, i));
				wall->setPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
				wall->_isTile = true;
				if (i == 0 || j == 0 || i == AssetsStorage::_layerHeight - 1 || j == AssetsStorage::_layerWidth - 1)
				{
					wall->_isBorder = true;
				}
				_drawbles.push_back(wall);
				wall = nullptr;
			}

		}
	}
}

void Map::draw()
{
	for (auto& i : _drawbles)
	{
		if (i->isActive())
		{
			i->draw();
		}
	}
}

void Map::update()
{
	for (auto& i : _drawbles)
	{
		i->update();
	}
}

MiniMap::MiniMap()
{
	init();
}

MiniMap::~MiniMap()
{
	for (auto& i : _drawbles)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = nullptr;
	}
	for (auto& i : _movebles)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = nullptr;
	}
	_movebles.clear();
}

void MiniMap::init()
{
	SpriteComponent* tile = new SpriteComponent(AssetsStorage::_miniMapTiles["gray"]);
	tile->setScaleDimension(_scaleDim * AssetsStorage::_layerWidth, _scaleDim * AssetsStorage::_layerHeight);
	tile->setOpacity(128);
	_drawbles.push_back(tile);
	tile = nullptr;

	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				SpriteComponent* wall = new SpriteComponent(AssetsStorage::_miniMapTiles["blackGray"]);
				wall->setPosition(Vector2T<int>(j * _scaleDim, i * _scaleDim));
				wall->setScaleDimension(_scaleDim, _scaleDim);
				wall->setOpacity(128);
				wall->_isMiniTile = true;
				_drawbles.push_back(wall);
			}
		}
	}

	for (auto& i : Mediator::getTanksPositions())
	{
		SpriteComponent* sprite = new SpriteComponent(AssetsStorage::_miniMapTiles[Mediator::getColorTeam(i.first)]);
		sprite->setPosition(i.second / AssetsStorage::_tileDim * _scaleDim);
		sprite->setScaleDimension(2 * _scaleDim, 2 * _scaleDim);
		sprite->_id = i.first;
		sprite->_isMiniTile = true;
		_movebles.push_back(sprite);
	}
}
void MiniMap::draw()
{
	for (auto& i : _drawbles)
	{
		if (isActive())
		{
			i->draw();
		}
	}
	for (auto& i : _movebles)
	{
		if (isActive())
		{
			i->draw();
		}
	}
}

void MiniMap::update()
{
	for (int i = 0; i < _drawbles.size(); i++)
	{
		if (!Mediator::stillExist(Mediator::getId({ _drawbles[i]->getPosition() / _scaleDim })))
		{
			_drawbles[i]->disable();
		}
		else
		{
			_drawbles[i]->enable();
		}
	}

	for (int i = 0; i < _movebles.size(); i++)
	{
		if (Mediator::stillExist(_movebles[i]->_id))
		{
			_movebles[i]->enable();
			_movebles[i]->setPosition(Mediator::getPosition(_movebles[i]->_id) / AssetsStorage::_tileDim * _scaleDim);
		}
		else
		{
			_movebles[i]->disable();
		}
	}

}

