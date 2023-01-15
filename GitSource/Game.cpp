#include"Engine.h"

int main(int argc, char* argv[])
{
	try
	{
		if (_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) < 0)
		{
			throw("Eroare la initilizarea sistemului de detectare al memory leakege-urilor!");
		}
		if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) < 0)
		{
			throw("Eroare la initlizarea sistemului de gestionare a sunetului!");
		}
		if (IMG_Init(IMG_INIT_PNG) < 0)
		{
			throw("Eroare la initlizarea sistemului de gestionare a imaginilor!");
		}
		if (TTF_Init() < 0)
		{
			throw("Eroare la initlizarea sistemului de gestionare a textului!");
		}
		if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) < 0)
		{
			throw("Eroare la initlizarea sistemului de gestionare a librariei generale!");
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			throw(Mix_GetError());
		}

		Engine game("Tank++", 1920, 1080, false, 60);

		game.run();

	}
	catch (const char* err)
	{
		std::cout << err << "\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}
