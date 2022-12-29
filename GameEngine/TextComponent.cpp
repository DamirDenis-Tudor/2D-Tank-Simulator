#include "TextComponent.h"

TTF_Font* TextComponent::_font = {};

TextComponent::TextComponent(SDL_Color color, int heigth ,string text , Vector2T<int> position)
{
	_textColor = color;
	
	_dest = new SDL_Rect;

	_dest->h = heigth;
	_dest->w = _dest->h * text.length() - 20;

	setCameraPosition(position);
	setText(text);

}

TextComponent::~TextComponent()
{
}

void TextComponent::setFont(const char* source)
{
	_font = TTF_OpenFont(source, 256);
}

Vector2T<int> TextComponent::getDimension()
{
	return Vector2T<int>(_dest->w, _dest->h);
}

void TextComponent::setText(string text)
{
	SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), _textColor );
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
	}
	_texture = SDL_CreateTextureFromSurface(RendererManager::_renderer, surface);
	_dest->w = 0.5 * _dest->h * text.length() ;

	SDL_FreeSurface(surface);
}
