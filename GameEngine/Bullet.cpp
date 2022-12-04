#include "Bullet.h"

Bullet::Bullet(string type, Vector2T<int> position, float angle, int tankId) : _position(position), _tankId(tankId)
{
	_sprite = new SpriteComponent(AssetsStorage::_movebles[{type, "bullet"}]);
	_sprite->setPosition(position - _sprite->_dest->w / 2);
	_sprite->_angle = angle;
	Mediator::notifyBulletsPosition(_position, _tankId, _id);
}

Bullet::~Bullet()
{
	_sprite->setNullPointers();
	delete _sprite;
	_sprite = nullptr;
}

void Bullet::update()
{
	Vector2T<float> potentialPos;
	potentialPos._x = _position._x;
	potentialPos._y = _position._y;

	potentialPos._x += _velocity._x * SDL_cos((_sprite->_angle - 90) * M_PI / 180) * TimeManager::getDeltaTime();
	potentialPos._y += _velocity._y * SDL_sin((_sprite->_angle - 90) * M_PI / 180) * TimeManager::getDeltaTime();

	bool hasCollision = false;

	if (CollisionManager::pointCollisionMap(potentialPos))
	{
		hasCollision = true;
	}

	int rectDim = 2 * AssetsStorage::_mapTileDim - 25;
	for (auto& i : Mediator::recieveTanksPosition(_tankId))
	{
		Vector2T<int> rectPos = i + 25;
		if (CollisionManager::pointCollisionRectagle(potentialPos, rectPos, rectDim))
		{
			hasCollision = true;
		}

	}
	//for (auto& i : Mediator::recieveBulletsPosition(_tankId, _id))
	//{
	////	pentru collisiunile bullet bullet check here
	//	if (CollisionManager::pointCollisionRectagle(potentialPos , i , rectDim ))
	//	{
	//		hasCollision = true;
	//	}
	//}

	if (hasCollision)
	{
		disable();
		Mediator::removeBulletsPosition(_tankId, _id);
	}
	else
	{
		_position._x = static_cast<int>(potentialPos._x);
		_position._y = static_cast<int>(potentialPos._y);

	}
	_sprite->setPosition(_position - CameraManager::offset - _sprite->_dest->w / 2);
}

void Bullet::draw()
{
	_sprite->draw();
}
