#pragma once

/*
* namespace with references to all the managers
*/

#include"RendererManager.h"

namespace managers
{
	RendererManager &_rendererManager = RendererManager::getInstance();
}