#include "TextComponent.h"

TTF_Font* TextComponent::_font = {};

TextComponent::TextComponent(SDL_Color color, int heigth ,string text , Vector2T<int> position)
{
	_text = text;
	_textColor = color;
	
	_dest = new SDL_Rect;

	_dest->h = heigth;
	_dest->w = _dest->h * text.length() - 20;

	_background = new SpriteComponent(AssetsStorage::_menuItems["infoPlate"]);

	_background->setScaleDimension(_dest->w, _dest->h);

	setCameraPosition(position);
	setBorder(true);
	setText(text);
}

TextComponent::~TextComponent()
{
	_background->setSrcTextNullPtr();
	delete _background;
	_background = nullptr;
}

void TextComponent::setFont(const char* source)
{
	_font = TTF_OpenFont(source,64);
}

void TextComponent::setColor(SDL_Color color)
{
	_textColor = color;
	SDL_Surface* surface = TTF_RenderText_Blended(_font, _text.c_str(), _textColor);
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
	}
	_texture = SDL_CreateTextureFromSurface(RendererManager::_renderer, surface);

	SDL_FreeSurface(surface);
}

Vector2T<int> TextComponent::getDimension()
{
	return Vector2T<int>(_dest->w, _dest->h);
}

void TextComponent::setText(string text)
{
	_text = text;
	SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), _textColor );
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
	}
	_texture = SDL_CreateTextureFromSurface(RendererManager::_renderer, surface);
	_dest->w = 0.5 * _dest->h * text.length() ;

	_background->setScaleDimension(_dest->w, _dest->h);

	SDL_FreeSurface(surface);
}

void TextComponent::setCameraPosition(Vector2T<int> position)
{
	_background->setCameraPosition(position);
	SpriteComponent::setCameraPosition(position);
}

void TextComponent::update()
{
	_background->update();
	SpriteComponent::update();
}

void TextComponent::draw()
{
	if (!isActive()) return;
	_background->draw();
	SpriteComponent::draw();
}
