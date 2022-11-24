#include"SpriteComponent.h"
#include"RendererManager.h"
#include"AssetsStorage.h"
#include <vector>



class Map :public Component
{
private:

	list<SpriteComponent*> _drawbles;
	static list<SpriteComponent*> _collidebles;

public:
	Map()
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
				}

			}
		}
	}

	void draw()  override
	{
		for (auto& i : _drawbles)
		{
			i->draw();
		}
	}

	void update() override
	{
		for (auto& i : _drawbles)
		{
			i->update();
		}
	}

};