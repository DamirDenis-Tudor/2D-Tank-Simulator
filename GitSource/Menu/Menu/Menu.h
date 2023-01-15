#pragma once
#include "Component.h"
#include "MenuScene.h"

class Menu : public Component
{
private:
	map<string , SpriteComponent*> _backgrounds;
	map<string, SpriteComponent*> _previews;
	vector<MenuScene*> _scenes;

	static string _mapName;
	static float _dificultyVal;
	
	static string _playerTeam;
	static string _playerType;
public:
	static bool _endGame;

	Menu();

	~Menu();

	void setSceneStatus(string name, bool status);
	void setButtonSceneStatus(string name, string button, bool status);

	static void setMapName(string name);

	static string getMapName();
	static string getPlayerTeam();
	static string getPlayerType();
	static float getDifficultyVar();

	string getPreviewTank()
	{
		string name;
		for (auto& preview : _previews)
		{
			if (preview.second->isActive())
			{
				name = preview.first;
			}
		}
		return name;
	}

	void menuLogic(MenuScene* scene);

	void update() override;
	void draw() override;
};

