#pragma once
#include"TextComponent.h"

/*
* Descriere clasa:
*	-> colecteaza toate obiectele de tip 
*	text si le deseneaza pe ecran cursiv
*/
class InfoManager : public Component
{
private:
	static map<string , TextComponent*> _aditionalInfo;
public:
	InfoManager();
	~InfoManager();

	static void addInfo(string , TextComponent*);
	static void setCameraPosition(string, Vector2T<int>);
	static void setText(string id, string text);
	static void setColor(string id, SDL_Color);
	static void disable(string);
	static void enable(string);
	static Vector2T<int> getDimension(string);

	void update() override;
	void draw() override;
};

