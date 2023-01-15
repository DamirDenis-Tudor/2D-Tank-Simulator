#include "Bullet.h"

Bullet::Bullet(string type, string impactAnim, int damage, Vector2T<int> position, float angle, int tankId) 
	: SpriteComponent(AssetsStorage::_movebles[{type, "bullet"}]) , _position(position), _tankId(tankId)  , _angle(angle), _damage(damage) , _impactAnim(impactAnim)
{
	setCameraPosition(position - getWidth() / 2 - CameraManager::offset);
	setAngle(angle);
}

Bullet::~Bullet()
{
	setSrcTextNullPtr();
}

void Bullet::update()
{
	SpriteComponent::update();

	/*
	* calculam pozitia viitoare
	*/
	Vector2T<float> potentialPos;
	potentialPos._x = _position._x;
	potentialPos._y = _position._y;

	potentialPos._x += _velocity._x * SDL_cos((getAngle() - 90) * M_PI / 180) * TimeManager::getDeltaTime();
	potentialPos._y += _velocity._y * SDL_sin((getAngle() - 90) * M_PI / 180) * TimeManager::getDeltaTime();

	bool hasCollision = false;
	
	
	/*
	* veriifcam coliziunea cu un obiect de pe mapa
	*/
	Vector2T<int> mapColliderObject;
	if (CollisionManager::pointCollisionMap(potentialPos , mapColliderObject))
	{
		Mediator::modifyHealth(Mediator::getId(mapColliderObject) , -_damage);
		
		if (Mediator::getHealth(Mediator::getId(mapColliderObject)) <= 0)
		{
			/*
			* daca obiectul este distrus inregistram cine l-a distrus
			* in cazul in care obiectul la randul lui distruge un tank 
			* echipa "ucigasusului" va primi un punct
			*/
			Mediator::registerKiller(Mediator::getId(mapColliderObject) , _tankId);
		}
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
			if (!Mediator::checkTeammates(_tankId, Mediator::getId(i)))
			{
				/*
				* daca nu sunt in aceeiasi echipa se poate
				* inregistra damage-ul
				*/
				Mediator::modifyHealth(Mediator::getId(i), -_damage);
				if (Mediator::getHealth(Mediator::getId(i)) <= 0)
				{
					/*
					* daca a avut loc decesul => punct
					*/
					Mediator::addPoint(Mediator::getColorTeam(_tankId));
					InfoManager::setText(Mediator::getColorTeam(_tankId) + "Points",
						to_string(Mediator::getTeamScore(Mediator::getColorTeam(_tankId))));
				}
			}
		}
	}

	if (hasCollision)
	{
		disable();
	}
	else
	{
		_position._x = static_cast<int>(potentialPos._x);
		_position._y = static_cast<int>(potentialPos._y);

	}

	setCameraPosition(_position - CameraManager::offset - getWidth() / 2);
}
