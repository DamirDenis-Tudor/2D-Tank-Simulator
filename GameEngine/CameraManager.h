#pragma once
#include"Vector2i.h"
class CameraManager
{
private:
	CameraManager() {}
public:
	static Vector2T<int> offset ;
	static Vector2T<int> pastOffset;
	static Vector2T<int> tileOffset;
	static Vector2T<int> startTileOffset;
};

