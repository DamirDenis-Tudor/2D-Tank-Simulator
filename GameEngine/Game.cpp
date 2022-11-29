#include"Engine.h"
/*
	RETODO :
		-> time manager
		-> modify movement classes
		-> add buulet class
		-> animation class
		-> add again animation
*/

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	Engine game("Tank++" , 1920 , 1080 , false , 60);

	game.run();

	return 0;
}
