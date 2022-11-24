#pragma 

#include"Vector2f.h"

class Circle
{
private:
	Vector2f _pos;
	float _r;

public:
	Circle() : _r(0) {}
	Circle(const Vector2f& pos, const float& r) :_pos(pos), _r(r) {}
	Circle(const Circle& circle) = default;
};

