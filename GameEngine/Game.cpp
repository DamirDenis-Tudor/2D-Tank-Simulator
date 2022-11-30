#include"Engine.h"
/*
	Todo::
		->animationManager -> deseneaza-le in engine
		asa vor aparea peste celelalte tank-uri;
*/

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	Engine game("Tank++" , 1920 , 1080 , false , 60);

	game.run();

	return 0;
}
