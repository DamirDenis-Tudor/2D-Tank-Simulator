#include"SpriteComponent.h"
#include"RendererManager.h"
#include"AssetsStorage.h"
#include <vector>

/*
	Descrierea clasei:
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

enum mapType {WorldMap , GuideMap};

class Map :public Component
{
protected:
	vector<SpriteComponent*> _drawbles;

public:

	Map(mapType type = WorldMap);
	virtual ~Map();

	void init();
	void draw()  override;
	void update() override;
};

class MiniMap : public Map
{
private:
	int _scaleDim = 6;
	map<int , SpriteComponent*> _movebles;
public:

	MiniMap();

	~MiniMap();

	void init() ;

	void draw() override;

	void update() override;
};

