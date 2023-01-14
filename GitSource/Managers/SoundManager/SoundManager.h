#include"Component.h"

/*
* Descriere clasa :
*	-> responsabila pentru gestionarea sunetelor
*	-> are o serie de sunete si in functie de comenzile externe
*   porneste un anumit sunet;
*/
class SoundManager : public Component
{
private:
	static map<string, Mix_Chunk*> _soundEfects;
	static map<string, Mix_Music*> _backgroundMelodies;
	SoundManager()
	{

	}

public:

	~SoundManager();

	static void addSoundEffect(const char* source, string id);
	static void addBackgroundMusic(const char* source, string id);

	static void playSoundEfect(string id , int volume = 100);
	
	static void playBackgroundMusic(string id);
	static void pauseBackgroundMusic(string id);

	static void clear();

};