#include "SoundManager.h"

map<string, Mix_Chunk*> SoundManager::_soundEfects = {};
map<string, Mix_Music*> SoundManager::_backgroundMelodies = {};

SoundManager::~SoundManager()
{
}

void SoundManager::addSoundEffect(const char* source, string id)
{
	_soundEfects.insert(pair<string, Mix_Chunk*>(id , Mix_LoadWAV(source)));
}

void SoundManager::addBackgroundMusic(const char* source, string id)
{
	_backgroundMelodies.insert(pair<string, Mix_Music*>(id, Mix_LoadMUS(source)));
}

void SoundManager::playSoundEfect(string id , int volume)
{
	Mix_PlayChannel(-1, _soundEfects[id], 0);
	Mix_VolumeChunk(_soundEfects[id], volume);
}

void SoundManager::playBackgroundMusic(string id)
{
	Mix_VolumeMusic(50);
	Mix_PlayMusic(_backgroundMelodies[id], -1);
}

void SoundManager::pauseBackgroundMusic(string id)
{
	Mix_PauseMusic();
}

void SoundManager::clear()
{
	for (auto& soundEffect : _soundEfects)
	{
		Mix_FreeChunk(soundEffect.second);
	}
	_soundEfects.clear();

	for (auto& melodie : _backgroundMelodies)
	{
		Mix_FreeMusic(melodie.second);
	}
	_backgroundMelodies.clear();
}


