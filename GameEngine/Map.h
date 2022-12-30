#include"SpriteComponent.h"
#include"RendererManager.h"
#include"AssetsStorage.h"
#include <vector>
#include"MapDestructibleObject.h"
#include"Barrel.h"

/*
	Descrierea clasei:
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
protected:
	vector<SpriteComponent*> _drawbles;

public:

	Map();
	~Map();

	void init();
	void draw()  override;
	void update() override;
};

/*
* Descriere clasa:
*	-> scaleaza obiectele pricipala de pe mapa
*	intr-o maniera mai superficiala 
*/
class MiniMap :public Component
{
private:
	int _scaleDim = 6;
	vector<SpriteComponent*> _drawbles;
	vector<SpriteComponent*> _movebles;
public:

	MiniMap();

	~MiniMap();

	void init() ;

	void draw() override;

	void update() override;
};

