#include"SpriteComponent.h"
#include"RendererManager.h"
#include"AssetsStorage.h"
#include <vector>

/*
	Descrierea clasei:
		
		-> apeleaza functiilor de draw , update pentru componentele mapei

		-> acceseaza tot ce este legat de un sprite folosind AssetsManager

		-> prin apelul constructorului se incarca tile-urile in vectorul de 
		   componente folosind constructorul de copiere al clasei SpriteComponent;
		* acest lucrul este mai optimal ; 
			exemplu:
			=> mapa : 3 layere , lungime 40 , inaltime 30 => 3600 de tile-uri
			   -> astfel in cel mai rau caz pot face 3600 de iteratii pentru 
			      a reprezenta mapa , dar acest caz este putin probabil;
				  nu pot avea un layer plin de collidere , sau unul plin de decoratiuni.
*/

class Map :public Component
{
private:

	list<Component*> _drawbles;

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

		//optimization -> reset couter
		SpriteComponent c;
		c.resetCouter();
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