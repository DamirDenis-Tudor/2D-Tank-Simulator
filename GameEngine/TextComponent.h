#pragma once
#include "SpriteComponent.h"
class TextComponent : public SpriteComponent
{
private:
	SDL_Color _textColor;
	TTF_Font* _font;
public:

	TextComponent(const char* fontSource);
	~TextComponent();

	Vector2T<int> getDimension();
	void setText(string text);
};

