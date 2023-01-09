#include "CameraManager.h"
#include "InfoManager.h"

int CameraManager::_tileDim = 0;
int CameraManager::_mapTilesWidth = 0;
int CameraManager::_mapTilesHeight = 0;
int CameraManager::_gameObjectId = 0;

Vector2T<int> CameraManager::_position = { 0,0 };
bool CameraManager::_spectatorMode = true;
Vector2T<int> CameraManager::offset = { 0,0 };
Vector2T<int> CameraManager::pastOffset = { 0,0 };
Vector2T<int> CameraManager::tileOffset = { 0,0 };


void CameraManager::init(int& tileDim, int& mapTilesWidth, int& mapTilesHeight)
{
	/*
	* text -> "Spectator Mode"
	*/
	InfoManager::addInfo("cam", new TextComponent(WHITE, 52, "SPECTATOR MODE"));
	InfoManager::setCameraPosition("cam", { RendererManager::_width / 2 - InfoManager::getDimension("cam")._x/2 , 64 });
	InfoManager::disable("cam");
	
	_tileDim = tileDim;
	_mapTilesHeight = mapTilesHeight;
	_mapTilesWidth = mapTilesWidth;
}

void CameraManager::cameraSync()
{
	CameraManager::pastOffset = CameraManager::offset;
	// verificam limitele mapei
	int horizontalBorder = _mapTilesWidth * _tileDim - RendererManager::_width;
	int verticalBorder = _mapTilesHeight * _tileDim- RendererManager::_heigth;

	Vector2T<int> position;
	if (_spectatorMode)
	{
		/*
		* daca suntem in modul spectator carema va putea fi miscata
		*/
		InfoManager::enable("cam");
		Vector2T<float> potentialPos = { (float)_position._x, (float)_position._y };
		Vector2T<float> direction(0, 0);

		if (InputManager::_up)
		{
			direction.setY(-1);
		}
		if (InputManager::_down)
		{
			direction.setY(1);
		}
		if (InputManager::_right)
		{
			direction.setX(1);
		}
		if (InputManager::_left)
		{
			direction.setX(-1);
		}

		// calculam pozitia viitoare
		potentialPos += Vector2T<float>{0.7, 0.7} * direction * TimeManager::getDeltaTime();
		position = { (int)potentialPos._x ,(int)potentialPos._y };
		if (position._x < RendererManager::_width / 2 - _tileDim)
		{
			position._x = RendererManager::_width / 2 - _tileDim;
		}
		if (position._y < RendererManager::_heigth / 2 -_tileDim)
		{
			position._y = RendererManager::_heigth / 2 - _tileDim;
		}

		if (position._x > horizontalBorder + RendererManager::_width / 2)
		{
			position._x = horizontalBorder + RendererManager::_width / 2;
		}
		if (position._y > verticalBorder + RendererManager::_heigth / 2)
		{
			position._y = verticalBorder + RendererManager::_heigth / 2;
		}
	}
	else
	{
		InfoManager::disable("cam");
		position = Mediator::getPosition(_gameObjectId);
	}

	CameraManager::offset.setX(position.getX() + _tileDim  - RendererManager::_width / 2);
	CameraManager::offset.setY(position.getY() + _tileDim - RendererManager::_heigth / 2);
	if (CameraManager::offset.getX() < 0)
	{
		CameraManager::offset.setX(0);
	}
	if (CameraManager::offset.getY() < 0)
	{
		CameraManager::offset.setY(0);
	}
	if (CameraManager::offset.getX() > horizontalBorder)
	{
		CameraManager::offset.setX(horizontalBorder);
	}
	if (CameraManager::offset.getY() > verticalBorder)
	{
		CameraManager::offset.setY(verticalBorder);
	}

	CameraManager::tileOffset = CameraManager::offset - CameraManager::pastOffset;

	_position = position;

}
