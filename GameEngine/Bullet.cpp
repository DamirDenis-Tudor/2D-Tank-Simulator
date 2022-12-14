#include "Bullet.h"

Bullet::Bullet(string type, Vector2T<int> position, float angle, int tankId) : _position(position), _tankId(tankId)
{
	_sprite = new SpriteComponent(AssetsStorage::_movebles[{type, "bullet"}]);
	_sprite->setPosition(position - _sprite->_dest->w / 2);
	_sprite->_angle = angle;
	Mediator::notifyBulletPosition(_position, _tankId, _id);
}

Bullet::~Bullet()
{
	_sprite->setSrcTextNullPtr();
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


	/*
		coliziuni bullet - tank
	*/
	int rectDim = 2 * AssetsStorage::_tileDim;
	for (auto& i : Mediator::recieveTanksPositions(_tankId))
	{
		Vector2T<int> rectPos = i ;
		if (CollisionManager::pointCollisionRectagle(potentialPos, rectPos, rectDim))
		{
			hasCollision = true;
			//daca are coliziune transmite-i tank-ului ca l-ai lovit (->damage )
		}
	}

	if (hasCollision)
	{
		disable();
		Mediator::removeBulletPosition(_tankId, _id);
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
