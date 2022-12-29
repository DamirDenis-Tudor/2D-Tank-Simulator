#include "AssetsStorage.h"

int AssetsStorage::_tileDim = 0;
map<set< string >, SpriteComponent* > AssetsStorage::_movebles = {};
vector<SpriteComponent* > AssetsStorage::_tiles = {};
int AssetsStorage::_barrelId = 0;
map<string, SpriteComponent*> AssetsStorage::_miniMapTiles = {};
int AssetsStorage::_layerWidth = 0;
int AssetsStorage::_layerHeight = 0;
SDL_Point* AssetsStorage::_rotCenter = new SDL_Point;
map<string, vector<vector<int>> > AssetsStorage::_mapLayers = {};
map<string, vector<SpriteComponent*>> AssetsStorage::_effects = {};

map<string, SpriteComponent*> AssetsStorage::_abilities = {};


void AssetsStorage::loadSprites(const char* sourceFile)
{
	XMLDocument document;

	document.LoadFile(sourceFile);


	if (document.Error())
	{
		//error printer
	}


	tinyxml2::XMLElement* root = document.RootElement();

	int dim = atoi(root->FindAttribute("dim")->Value());
	
	//centrul de rotatie al cannon-ului
	_rotCenter->x = (atoi(root->FindAttribute("rotationX")->Value()));
	_rotCenter->y = (atoi(root->FindAttribute("rotationY")->Value()));
	
	SpriteComponent::center = *_rotCenter;

	//incarcare sprite-uri bodies

	tinyxml2::XMLElement* body = root->FirstChildElement("body");

	for(auto i = body->FirstChildElement() ; i != body->LastChildElement() ; i = i->NextSiblingElement() )
	{
		
		SpriteComponent* sprite = new SpriteComponent(i->FirstChildElement()->FindAttribute("source")->Value() , dim , dim);

		_movebles.insert(pair < set <string >, SpriteComponent* >
			( { "body" ,i->FindAttribute("type")->Value() , i->FindAttribute("color")->Value() } , sprite));

	}
	body = nullptr;

	//incarcare sprite-uri cannons

	tinyxml2::XMLElement* cannon = root->FirstChildElement("cannon");

	for (auto i = cannon->FirstChildElement("tileset"); i != cannon->LastChildElement(); i = i->NextSiblingElement())
	{

		SpriteComponent* sprite = new SpriteComponent(i->FirstChildElement()->FindAttribute("source")->Value() , dim , dim);

		_movebles.insert(pair < set < string >, SpriteComponent* >
			({ "cannon" ,i->FindAttribute("type")->Value() , i->FindAttribute("color")->Value() }, sprite));

	}

	cannon = nullptr;

	//incarcare sprite-uri bullets
	tinyxml2::XMLElement* bullet = root->FirstChildElement("bullet");

	for (auto i = bullet->FirstChildElement(); i != bullet->LastChildElement(); i = i->NextSiblingElement())
	{

		SpriteComponent* sprite = new SpriteComponent(i->FirstChildElement()->FindAttribute("source")->Value() , dim , dim);

		_movebles.insert(pair < set <string >, SpriteComponent* >
			({ "bullet" ,i->FindAttribute("type")->Value() }, sprite));

	}

	//incarcare sprite-uri tracks

	tinyxml2::XMLElement* tracks = root->FirstChildElement("tracks");
	SpriteComponent* sprite = new SpriteComponent(tracks->FirstChildElement()->FindAttribute("source")->Value() , dim , dim);

	_movebles.insert(pair < set <string >, SpriteComponent* > ({ "atracks"}, sprite));

	tracks = nullptr;

	root = nullptr;

	document.Clear();

}

void AssetsStorage::loadAbilities(const char* sourceFile)
{
	XMLDocument document;

	document.LoadFile(sourceFile);

	if (document.Error())
	{
		std::cout << "Eroare : cale inexistenta catre fisierul level !\n";
		exit(EXIT_FAILURE);
	}

	tinyxml2::XMLElement* root = document.RootElement(); // items

	for (auto ability = root->FirstChildElement("ability"); ability != root->LastChildElement("ability"); ability = ability->NextSiblingElement("ability"))
	{
		int dim = atoi(root->FindAttribute("dim")->Value());
		_abilities.insert(pair<string, SpriteComponent*>
			(ability->FindAttribute("name")->Value(),
				new SpriteComponent(ability->FirstChildElement()->FindAttribute("source")->Value(),
					dim , dim)));
	}
}

void AssetsStorage::loadTiles(const char* sourceFile)
{	
	XMLDocument document;

	document.LoadFile(sourceFile);

	if (document.Error())
	{
		std::cout << "Eroare : cale inexistenta catre fisierul level !\n";
		exit(EXIT_FAILURE);
	}

	tinyxml2::XMLElement* root = document.RootElement(); // map

	//load map info
	_tileDim = atoi(root->FindAttribute("tilewidth")->Value());

	tinyxml2::XMLElement* child = root->FirstChildElement("tileset");

	const char* source = nullptr;

	//daca am sprite-uri mai mare de dimesiunea unui tile 
	//trebuie sa le incarc in memorie segmentate
	int dim = 0;
	int tileCount = 0;
	int colums = 0;
	int rows = 0;

	for (child; child != root->LastChildElement("tileset");
		child = child->NextSiblingElement("tileset"))
	{
		dim = atoi(child->FindAttribute("tilewidth")->Value());
		tileCount = atoi(child->FindAttribute("tilecount")->Value());
		colums = atoi(child->FindAttribute("columns")->Value());
		source = child->FirstChildElement("image")->FindAttribute("source")->Value();
		source = source + 3; // sursa are formatul cu adresa relativa '../' 

		if (strcmp(child->FindAttribute("name")->Value() , "Barell_02") == 0 )
		{
			_barrelId = atoi(child->FindAttribute("firstgid")->Value());
		}

		if (tileCount == 1) //caz 1
		{
			SpriteComponent* sprite = new SpriteComponent(source , dim , dim);

			_tiles.push_back(sprite);

			sprite = nullptr;
		}
		else //caz 2
		{
			rows = tileCount / colums;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < colums; j++)
				{
					SpriteComponent* sprite = new SpriteComponent(source , _tileDim , _tileDim);
					sprite->_src->x = j * _tileDim;
					sprite->_src->y = i * _tileDim;

					_tiles.push_back(sprite);

					sprite = nullptr;
				}
			}
		}
	}

	//load map

	child = root->FirstChildElement("layer");

	_layerWidth = atoi(child->FindAttribute("width")->Value());
	_layerHeight = atoi(child->FindAttribute("height")->Value());

	const char* buffer = nullptr;

	for (child; child <= root->LastChildElement("layer");
		child = child->NextSiblingElement("layer"))
	{
		std::vector< std::vector<int> > mapLayer;
		buffer = child->FirstChildElement("data")->FirstChild()->Value();
		string name = child->FindAttribute("name")->Value();

		convertInToMatrix(buffer, mapLayer);// matricea nivelului este stocata 
											 // printr-un sir de caractere continad
											// ',' , '\n' , indexi cu pana la 3 cifre
		_mapLayers.insert(pair<string, vector< vector<int> > > (name, mapLayer));

		mapLayer.clear();

		if (child == root->LastChildElement("layer"))
		{
			break;
		}
	}

	child = nullptr;

	document.Clear();
}
void AssetsStorage::convertInToMatrix(const char* buffer, std::vector<std::vector<int>>& mapLayer)
{
	//functia are in vedere faptul ca id-ul unui sprite nu poate depasi 999
	buffer++; //first is \n

	std::vector<int> line;

	while (*buffer != '\0')
	{

		char convertbleString[3] = { '\0' }; //convert 'xxx' -> xxx
		if (*buffer != ',' && *buffer != '\n')
		{
			convertbleString[0] = *buffer;
			if (*(buffer + 1) != ',')
			{
				convertbleString[1] = *(buffer + 1);
				buffer++;
			}
			if (*(buffer + 1) != ',')
			{
				convertbleString[2] = *(buffer + 1);
				buffer++;
			}

			line.push_back(atoi(convertbleString));
		}
		if (*buffer == '\n')
		{
			mapLayer.push_back(line);
			line.clear();
		}
		buffer++;
	}

}

void AssetsStorage::loadMiniTiles(const char* sourceFile)
{
	XMLDocument document;

	document.LoadFile(sourceFile);

	if (document.Error())
	{
		std::cout << "Eroare : cale inexistenta catre fisierul level !\n";
		exit(EXIT_FAILURE);
	}

	XMLElement* root = document.RootElement();

	for (XMLElement *child = root->FirstChildElement("image"); child != root->LastChildElement("image");
		child = child->NextSiblingElement("image"))
	{
		SpriteComponent* sprite = new SpriteComponent(child->FindAttribute("source")->Value());
		sprite->_src->x = 0;
		sprite->_src->y = 0;
		sprite->_src->w = atoi(child->FindAttribute("width")->Value());
		sprite->_src->h = atoi(child->FindAttribute("height")->Value());

		sprite->_dest->x = 0;
		sprite->_dest->y = 0;
		sprite->_dest->w = atoi(child->FindAttribute("width")->Value());
		sprite->_dest->h = atoi(child->FindAttribute("height")->Value());

		_miniMapTiles.insert(pair<string, SpriteComponent*> (child->FindAttribute("color")->Value(), sprite));

		sprite = nullptr;
	}
}

void AssetsStorage::loadEffects(const char* sourceFile)
{
	XMLDocument document;

	document.LoadFile(sourceFile);


	if (document.Error())
	{
		//error printer
	}

	XMLElement* root = document.RootElement();
	
	for (auto i = root->FirstChildElement("animation"); i != root->LastChildElement(); i = i->NextSiblingElement())
	{
		int dim = atoi(i->FindAttribute("dim")->Value());
		vector<SpriteComponent*> effect;
		string type = i->FindAttribute("type")->Value();
		for (auto j = i->FirstChildElement("image");
			j != i->LastChildElement(); j = j->NextSiblingElement())
		{
			const char* name = j->FindAttribute("source")->Value();
			SpriteComponent* sprite = new SpriteComponent(name , dim , dim);

			effect.push_back(sprite);

			sprite = nullptr;
		}

		_effects.insert(pair<string, vector<SpriteComponent*>>(type, effect));
		effect.clear();
	}

	document.Clear();
}

void AssetsStorage::clear()
{
	for (auto x = _movebles.begin(); x != _movebles.end(); x++)
	{
		delete x->second;
		x->second = 0;
	}
	_movebles.clear();

	for (int i = 0; i < _tiles.size(); i++)
	{
		delete _tiles[i];
		_tiles[i] = 0;
	}
	_tiles.clear();

	for (auto &i : _miniMapTiles)
	{
		delete i.second;
		i.second = nullptr;
	}
	_miniMapTiles.clear();

	for (auto& x : _effects)
	{
		for (int i = 0; i < size(_effects[x.first]); i++)
		{
			delete _effects[x.first][i];
			_effects[x.first][i] = 0;
		}
		_effects[x.first].clear();
	}
	_effects.clear();

	for (auto& i : _abilities)
	{
		delete i.second;
		i.second = nullptr;
	}
	_abilities.clear();

	delete _rotCenter;
}
