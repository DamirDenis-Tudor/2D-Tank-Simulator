#include"TankBuilder.h"

void TankBuilder::setAtrributes(const char* type, const char* color,
	Vector2T<int> position, Vector2T<float> velocity, float shootingTime)
{
	_type = type;
	_color = color;
	_position = position;
	_velocity = velocity;
	_shootingTime = shootingTime;
}

void TankBuilder::build()
{
	setBehavior();
	SpriteComponent* tracks = new SpriteComponent(AssetsStorage::_movebles[{"tracks"}]);
	SpriteComponent* body = new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "body"}]);
	SpriteComponent* cannon = new SpriteComponent(AssetsStorage::_movebles[{_color, _type, "cannon"}]);

	_result = new Tank(tracks, body, cannon, _behavior, _position, _velocity, _shootingTime, _type);

	if (playerIdentifier)
	{
		Mediator::setPlayerId(_result->_id);
		CameraManager::setFocusId(_result->_id);
	}
}