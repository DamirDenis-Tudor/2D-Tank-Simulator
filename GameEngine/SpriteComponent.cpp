#include "SpriteComponent.h"
#include "Map.h"

SDL_Point SpriteComponent::center = {};

void SpriteComponent::draw()
{
	/*
		un sprite este desenat pe ecran doar daca
		este un obiect desenabil activ
	*/
	if (_isObjectDrawble && isActive() )
	{
		SDL_RenderCopyEx(RendererManager::_renderer, _texture, _src, _dest, _angle, &center, SDL_FLIP_NONE);

		/*
		* in cazul minimapei suplimetam randarea 
		* cu cate un henar in jurul fiecarui obiect
		* (este mai mult de "design")
		*/
		if (_isMiniTile)
		{
			SDL_RenderDrawRect(RendererManager::_renderer, _dest);
		}
	}
}

void SpriteComponent::update()
{
	/*
	* daca obiectul este urmarit
	* implicit offseturile camerei sunt calculate
	* in functie de el
	*/
	if (_isFollowed) return;

	/*
	* daca nu este urmarit
	* stabilim daca este sau nu
	* in cadrul camerei
	*/
	isOnCamera();

	/*
	* obiectele de pe mapa
	* trebuie miscate cu un 
	* offset calculat frame by frame
	* pentru a crea efectul de "camera"
	*/
	if (_isMapObject)
	{
		_dest->x = _dest->x - CameraManager::tileOffset._x;
		_dest->y = _dest->y - CameraManager::tileOffset._y;
	}
}

void SpriteComponent::isOnCamera()
{
	if (_dest->x + _dest->w  < -64 ||
		_dest->y + _dest->h  < -64 ||
		_dest->x  > RendererManager::_width + 64  ||
		_dest->y  > RendererManager::_heigth + 64 )
	{
		/*
		* daca nu mai este in cadrul camerei
		* nu il mai randam
		*/
		_isObjectDrawble = false;
	}
	else
	{
		/*
		* daca este in cadrul camerei
		* il activam doar daca obiectul 
		* nu a fost setat temporar inactiv 
		* prin distrugere
		*/
		if (!(_isSpawnble && !isActive()))
		{
			_isObjectDrawble = true;
		}
	}
}

SpriteComponent::SpriteComponent(const char* source, int sourceDim, int destDim)
{
	_src = new SDL_Rect;
	_dest = new SDL_Rect;

	_src->x = 0;
	_src->y = 0;
	_src->w = sourceDim;
	_src->h = sourceDim;

	_dest->x = 0;
	_dest->y = 0;
	_dest->w = destDim;
	_dest->h = destDim;

	SDL_Surface* surface = IMG_Load(source);
	_texture = SDL_CreateTextureFromSurface(RendererManager::getRenderer(), surface);
	SDL_FreeSurface(surface);
}

SpriteComponent::SpriteComponent(SpriteComponent*& sprite)
{
	/*
	* realizeaza o "copie" a unui sprite existent
	*/
	_src = sprite->_src;

	_dest = new SDL_Rect;
	*_dest = *sprite->_dest;

	_texture = sprite->_texture;
}

SpriteComponent::~SpriteComponent()
{
	if (_src != nullptr)
	{
		delete(_src);
		_src = nullptr;
	}
	if (_dest != nullptr)
	{
		delete(_dest);
		_dest = nullptr;
	}
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}
