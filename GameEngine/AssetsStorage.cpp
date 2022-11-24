#include "AssetsStorage.h"

//AssetsStorage* AssetsStorage::_instance = nullptr;
int AssetsStorage::_mapTileDim = 0;
map<set< string >, SpriteComponent* > AssetsStorage::_movebles = {};
vector<SpriteComponent* > AssetsStorage::_tiles = {};
int AssetsStorage::_layerWidth = 0;
int AssetsStorage::_layerHeight = 0;

SDL_Point* AssetsStorage::_rotCenter = new SDL_Point;

map<string, vector<vector<int>> > AssetsStorage::_mapLayers = {};

/*
	* tank (root) -> bodies		 |
	*			  -> cannons	 |
	*			  -> bullets	 |
	*			  -> tracks      |
	*			  -> effects     |
	*
	* <tank ....
	*
	*	<body - atributes
	*		<tileset - atributes ..
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	*	<cannons - atributes
	*		<tileset - atributes
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	*	<bullets - atributes
	*		<tileset - atributes
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	* 	<tracks - atributes
	*		<tileset - atributes
	*			<image - atributes
	*			.
	*			.
	*			.
	*			.
	* 	<effects - atributes
	*		<tileset - atributes
	*			<image - atributes
	*
	*
	* <tank/>
	*/

void AssetsStorage::loadMovebles(const char* sourceFile)
{
	XMLDocument document;

	document.LoadFile("assets/sTanks/tank.tmx");


	if (document.Error())
	{
		//error printer
	}


	tinyxml2::XMLElement* root = document.RootElement();

	int dim = atoi(root->FindAttribute("dim")->Value());

	_rotCenter->x = (atoi(root->FindAttribute("rotationX")->Value()));
	_rotCenter->y = (atoi(root->FindAttribute("rotationY")->Value()));

	tinyxml2::XMLElement* body = root->FirstChildElement("body");

	for(auto i = body->FirstChildElement() ; i != body->LastChildElement() ; i = i->NextSiblingElement() )
	{
		
		SpriteComponent* sprite = new SpriteComponent(i->FirstChildElement()->FindAttribute("source")->Value());
		
		sprite->_src->x = 0;
		sprite->_src->y = 0;
		sprite->_src->w = dim;
		sprite->_src->h = dim;

		sprite->_dest->x = 0;
		sprite->_dest->y = 0;
		sprite->_dest->w = dim;
		sprite->_dest->h = dim;


		_movebles.insert(pair < set <string >, SpriteComponent* >
			( { "body" ,i->FindAttribute("type")->Value() , i->FindAttribute("color")->Value() } , sprite));

	}

	tinyxml2::XMLElement* cannon = root->FirstChildElement("cannon");

	for (auto i = cannon->FirstChildElement("tileset"); i != cannon->LastChildElement(); i = i->NextSiblingElement())
	{

		SpriteComponent* sprite = new SpriteComponent(i->FirstChildElement()->FindAttribute("source")->Value());

		sprite->_src->x = 0;
		sprite->_src->y = 0;
		sprite->_src->w = dim;
		sprite->_src->h = dim;

		sprite->_dest->x = 0;
		sprite->_dest->y = 0;
		sprite->_dest->w = dim;
		sprite->_dest->h = dim;

		_movebles.insert(pair < set < string >, SpriteComponent* >
			({ "cannon" ,i->FindAttribute("type")->Value() , i->FindAttribute("color")->Value() }, sprite));

	}

	tinyxml2::XMLElement* bullet = root->FirstChildElement("bullet");

	for (auto i = bullet->FirstChildElement(); i != bullet->LastChildElement(); i = i->NextSiblingElement())
	{

		SpriteComponent* sprite = new SpriteComponent(i->FirstChildElement()->FindAttribute("source")->Value());

		sprite->_src->x = 0;
		sprite->_src->y = 0;
		sprite->_src->w = dim;
		sprite->_src->h = dim;

		sprite->_dest->x = 0;
		sprite->_dest->y = 0;
		sprite->_dest->w = dim;
		sprite->_dest->h = dim;


		_movebles.insert(pair < set <string >, SpriteComponent* >
			({ "bullet" ,i->FindAttribute("type")->Value() , i->FindAttribute("color")->Value() }, sprite));

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
	_mapTileDim = atoi(root->FindAttribute("tilewidth")->Value());

	tinyxml2::XMLElement* child = root->FirstChildElement("tileset");

	// data interes
	const char* source = nullptr;
	int tileWidth = 0;
	int tileHeight = 0;
	int tileCount = 0;
	int colums = 0;
	int rows = 0;

	for (child; child != root->LastChildElement("tileset");
		child = child->NextSiblingElement("tileset"))
	{
		tileWidth = atoi(child->FindAttribute("tilewidth")->Value());
		tileHeight = atoi(child->FindAttribute("tileheight")->Value());
		tileCount = atoi(child->FindAttribute("tilecount")->Value());
		colums = atoi(child->FindAttribute("columns")->Value());
		source = child->FirstChildElement("image")->FindAttribute("source")->Value();

		source = source + 3; // sursa are formatul cu adresa relativa '../' 

		if (tileCount == 1) //caz 1
		{
			SpriteComponent* sprite = new SpriteComponent(source);
			sprite->_src->x = 0;
			sprite->_src->y = 0;
			sprite->_src->w = tileWidth;
			sprite->_src->h = tileHeight;

			sprite->_dest->x = 0;
			sprite->_dest->y = 0;
			sprite->_dest->w = tileWidth;
			sprite->_dest->h = tileHeight;

			_tiles.push_back(sprite);
		}
		else //caz 2
		{
			rows = tileCount / colums;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < colums; j++)
				{
					SpriteComponent* sprite = new SpriteComponent(source);
					sprite->_src->x = j * _mapTileDim;
					sprite->_src->y = i * _mapTileDim;
					sprite->_src->w = _mapTileDim;
					sprite->_src->h = _mapTileDim;

					sprite->_dest->x = 0;
					sprite->_dest->y = 0;
					sprite->_dest->w = _mapTileDim;
					sprite->_dest->h = _mapTileDim;

					_tiles.push_back(sprite);
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

		if (child == root->LastChildElement("layer"))
		{
			break;
		}
	}


	document.Clear();
}

void AssetsStorage::convertInToMatrix(const char* buffer, std::vector<std::vector<int>>& mapLayer)
{

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