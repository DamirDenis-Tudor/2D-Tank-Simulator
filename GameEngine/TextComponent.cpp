#include "TextComponent.h"

TextComponent::TextComponent(const char* fontSource) 
{
	_textColor = { 128,0,0 };
	
	_dest = new SDL_Rect;
	_dest->w = 64;
	_dest->h = 24;

	_font = TTF_OpenFont(fontSource , 64);
}

TextComponent::~TextComponent()
{
	TTF_CloseFont(_font);
}

Vector2T<int> TextComponent::getDimension()
{
	return Vector2T<int>(_dest->w, _dest->h);
}

void TextComponent::setText(string text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(_font, text.c_str(), _textColor);
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
	}
	_texture = SDL_CreateTextureFromSurface(RendererManager::_renderer, surface);
	SDL_FreeSurface(surface);
}
