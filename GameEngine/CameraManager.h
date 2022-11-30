#pragma once
#include"Vector2i.h"

/*
	Descrierea clasei:

		->in viitor va implemeta o metoda statica de sync
		si una de zoom in  , out
*/

class CameraManager
{
private:
	CameraManager() {}
public:
	static Vector2T<int> offset ;
	static Vector2T<int> pastOffset;
	static Vector2T<int> tileOffset;
};

