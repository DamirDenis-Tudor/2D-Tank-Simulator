#pragma once
#include "SpriteComponent.h"
#include "AssetsStorage.h"

#define BLACK {0 ,0 ,0 }
#define WHITE {255, 255 , 255}

#define RED {252, 121, 123}

#define GREEN {0, 255 ,0 , 0 }
#define BLUE {71, 124 , 249 }
#define BROWN {181,103,33}
#define YELLOW {255 , 255 , 0}
#define GOLD {255,223,0}

//gaseste o solutie pt pozitii
#define TextScoreBoardHeight 64
#define YellowTeamScorePosition {1600 , 0}
#define GreenTeamScorePosition {1600 , 64}
#define BlueTeamScorePosition {1600 , 128}
#define BrownTeamScorePosition {1600, 192}

/*
	Descriere clasa:
		-> clasa responsabila pentru gestionare entitailor de tip text
*/

class TextComponent : public SpriteComponent
{
private:
	SpriteComponent* _background = nullptr;
	SDL_Color _textColor = {};
	static TTF_Font* _font;
	string _text;
public:

	TextComponent(){}
	TextComponent(SDL_Color color , int heigth , string text = " ", Vector2T<int> position = {0,0});
	~TextComponent();

	static void setFont(const char*);
	
	void setColor(SDL_Color color);
	Vector2T<int> getDimension();
	void setText(string text);
	void setCameraPosition(Vector2T<int> position);

	void update() override;
	void draw() override;
};

