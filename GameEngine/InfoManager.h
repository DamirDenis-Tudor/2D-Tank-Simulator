#pragma once
#include"TextComponent.h"
class InfoManager : public Component
{
private:
	static map<string , TextComponent*> _aditionalInfo;
public:
	InfoManager();
	~InfoManager();

	static void addInfo(string , TextComponent*);
	static void setPosition(string, Vector2T<int>);
	static void setText(string , string );
	static void disable(string);
	static void enable(string);
	static Vector2T<int> getDimension(string);

	void update() override;
	void draw() override;
};

