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

class Map :public Component
{
private:
	vector<SpriteComponent*> _drawbles;

public:

	Map();
	~Map();

	void draw()  override;
	void update() override;
};