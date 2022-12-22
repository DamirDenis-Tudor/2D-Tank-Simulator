#pragma once
#include"Component.h"
class InfoManager : public Component
{
private:

public:
	InfoManager();
	~InfoManager();

	void update() override;
	void draw() override;
};

