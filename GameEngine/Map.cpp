#include"Map.h"


Map::Map(mapType type)
{
	if (type == WorldMap)
	{
		init();
	}
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
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_tiles[AssetsStorage::_mapLayers["colidble"][i][j] - 1]);
				tile->setPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
				tile->_isTile = true;
				_drawbles.push_back(tile);
				tile = nullptr;
			}

		}
	}
}

void Map::draw()
{
	for (auto& i : _drawbles)
	{
		i->draw();
	}
}

void Map::update()
{
	for (auto& i : _drawbles)
	{
		i->update();
	}
}

MiniMap::MiniMap() : Map(GuideMap)
{
	init();
}

MiniMap::~MiniMap()
{
	for (auto& i : _movebles)
	{
		i.second->setSrcTextNullPtr();
		delete i.second;
		i.second = nullptr;
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
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_miniMapTiles["blackGray"]);
				tile->setPosition(Vector2T<int>(j * _scaleDim, i * _scaleDim));
				tile->setScaleDimension(_scaleDim, _scaleDim);
				tile->setOpacity(128);
				tile->_isMiniTile = true;
				_drawbles.push_back(tile);
			}
		}
	}

	for (auto& i : Mediator::getTanksPositions())
	{
		SpriteComponent* sprite = new SpriteComponent(AssetsStorage::_miniMapTiles[Mediator::getColorTeam(i.first)]);
		sprite->setPosition(i.second / AssetsStorage::_tileDim * _scaleDim);
		sprite->setScaleDimension(2 * _scaleDim, 2 * _scaleDim);
		sprite->_isMiniTile = true;
		_movebles.insert(pair<int, SpriteComponent*>(i.first, sprite));
	}
}
void MiniMap::draw()
{
	Map::draw();
	for (auto& i : _movebles)
	{
		i.second->draw();
	}
}

void MiniMap::update()
{
	for (auto& i : _movebles)
	{
		i.second->setPosition(Mediator::getPosition(i.first) / AssetsStorage::_tileDim * _scaleDim);
	}
}

