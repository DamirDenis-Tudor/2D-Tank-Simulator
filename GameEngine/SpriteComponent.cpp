#include "SpriteComponent.h"

void SpriteComponent::draw()
{
	if (isActive())
	{
		SDL_RenderCopyEx(RendererManager::_renderer, _texture, _src, _dest, _angle, &center, SDL_FLIP_NONE);

		if (!_isTile)
		{
		//	SDL_RenderDrawRect(RendererManager::_renderer, _dest);
		}
	}
}

void SpriteComponent::update()
{
	if (!_isFollowed)
	{
		isOnCamera();

		if(_isTile)
		{
			_dest->x = _dest->x - CameraManager::tileOffset._x;
			_dest->y = _dest->y - CameraManager::tileOffset._y;
		}
	}
}

void SpriteComponent::isOnCamera()
{
	if (_dest->x + _dest->w  < -64 ||
		_dest->y + _dest->h  < -64 ||
		_dest->x  > RendererManager::_width + 64 ||
		_dest->y  > RendererManager::_heigth + 64)
	{
		disable();
	}
	enable();
}

SpriteComponent::SpriteComponent(const char* source)
{
	_src = new SDL_Rect;
	_dest = new SDL_Rect;
	SDL_Surface* surface = IMG_Load(source);
	_texture = SDL_CreateTextureFromSurface(RendererManager::getRenderer(), surface);
	SDL_FreeSurface(surface);
}

SpriteComponent::SpriteComponent(SpriteComponent*& sprite)
{
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
