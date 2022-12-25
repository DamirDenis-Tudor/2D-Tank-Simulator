#pragma once
#include<iostream>
#include <string>
#include<math.h>

class Vector2f
{
private:
	float _x, _y;

public:
	Vector2f() : _x(0), _y(0) { }
	Vector2f(const Vector2f& newVector2f) :_x(newVector2f._x), _y(newVector2f._y) {}
	Vector2f(const float x, const float y) :_x(x), _y(y) { }

	//rvalue op with vector
	Vector2f operator + (const Vector2f& vector)
	{
		return Vector2f(vector._x + this->_x, vector._y + this->_y);
	}

	Vector2f operator - (const Vector2f& vector)
	{
		return Vector2f(vector._x - this->_x, vector._y - this->_y);
	}

	Vector2f operator * (const Vector2f& vector)
	{
		return Vector2f(vector._x * this->_x, vector._y * this->_y);
	}

	Vector2f operator / (const Vector2f& vector)
	{
		return Vector2f(vector._x / this->_x, vector._y / this->_y);
	}

	//rvalue op with value

	Vector2f operator + (const float& value)
	{
		return Vector2f(this->_x + value, this->_y + value);
	}

	Vector2f operator - (const float& value)
	{
		return Vector2f(this->_x - value, this->_y - value);
	}

	Vector2f operator * (const float& value)
	{
		return Vector2f(this->_x * value, this->_y * value);
	}

	Vector2f operator / (const float& value)
	{
		return Vector2f(this->_x / value, this->_y / value);
	}

	//lvalue op with vector
	Vector2f& operator += (const Vector2f& vector)
	{
		this->_x += vector._x;
		this->_y += vector._y;

		return *this;
	}

	Vector2f& operator -= (const Vector2f& vector)
	{
		this->_x -= vector._x;
		this->_y -= vector._y;

		return *this;
	}

	Vector2f& operator *= (const Vector2f& vector)
	{
		this->_x *= vector._x;
		this->_y *= vector._y;

		return *this;
	}

	Vector2f& operator /= (const Vector2f& vector)
	{
		this->_x /= vector._x;
		this->_y /= vector._y;

		return *this;
	}

	//lvalue op with value
	Vector2f& operator += (const float& value)
	{
		this->_x += value;
		this->_y += value;

		return *this;
	}

	Vector2f& operator -= (const float& value)
	{
		this->_x -= value;
		this->_y -= value;

		return *this;
	}

	Vector2f& operator *= (const float& value)
	{
		this->_x *= value;
		this->_y *= value;

		return *this;
	}

	Vector2f& operator /= (const float& value)
	{
		this->_x /= value;
		this->_y /= value;

		return *this;
	}

	//compare
	bool operator == (const Vector2f& vector)
	{
		return (this->_x == vector._x && this->_y == vector._y);
	}

	bool operator != (const Vector2f& vector)
	{
		return (this->_x != vector._x && this->_y != vector._y);
	}

	//getters and setters
	float getX()const
	{
		return _x;
	}
	void setX(const float& x)
	{
		_x = x;
	}
	float getY()const
	{
		return _y;
	}
	void setY(const float& y)
	{
		_y = y;
	}

	//print 

	const std::string strVector2f() const
	{
		return "(" + std::to_string(_x) + "," + std::to_string(_y) + ")";
	}


	friend std::ostream& operator << (std::ostream& os, const Vector2f& vector)
	{
		os << vector.strVector2f() << "\n";
		return os;
	}

	//formulas
	const float mag() 
	{
		return sqrt(this->_x * this->_x + this->_y * this->_y);
	}

	Vector2f norm()
	{
		Vector2f newVector = *this;
		return newVector / newVector.mag();
	}

};


