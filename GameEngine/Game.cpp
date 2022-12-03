#define _CRTDBG_MAP_ALLOC
#include"Engine.h"
#include<crtdbg.h>
#
/*
	Todo::
		->animationManager -> deseneaza-le in engine
		asa vor aparea peste celelalte tank-uri;

		make couter component resetble
		
		->lucreaza cu smartPointers 
*/

//ai grija cand iterezi prin vector
// daca dai vector.size() asat se modifica la fiecare iteratie



int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	Engine game("Tank++" , 780 , 420 , false , 60);

	game.run();

	game.clear();

	return 0;
}
