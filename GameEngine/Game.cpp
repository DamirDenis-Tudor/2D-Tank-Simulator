#include"Engine.h"
/*
	Todo::
		->animationManager -> deseneaza-le in engine
		asa vor aparea peste celelalte tank-uri;

		make couter component resetble
*/

//ai grija cand iterezi prin vector
// daca dai vector.size() asat se modifica la fiecare iteratie

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	Engine game("Tank++" , 780 , 420 , false , 60);

	game.run();

	game.clear();

	return 0;
}
