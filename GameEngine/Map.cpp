#include"Map.h"

Map::Map()
{
	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["ground"][i][j] != 0)
			{
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_tiles[AssetsStorage::_mapLayers["ground"][i][j] - 1]);
				tile->setPosition(Vector2T<int>(j * AssetsStorage::_mapTileDim, i * AssetsStorage::_mapTileDim));

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
				tile->setPosition(Vector2T<int>(j * AssetsStorage::_mapTileDim, i * AssetsStorage::_mapTileDim));
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
				tile->setPosition(Vector2T<int>(j * AssetsStorage::_mapTileDim, i * AssetsStorage::_mapTileDim));
				_drawbles.push_back(tile);
				tile = nullptr;
			}

		}
	}
}

Map::~Map()
{
	for (auto& i : _drawbles)
	{
		i->setNullPointers();
		delete i;
		i = 0;
	}
	_drawbles.clear();
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
