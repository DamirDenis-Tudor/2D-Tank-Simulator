#pragma once
#include<iostream>
#include <string>
#include<math.h>


template<typename T>
class Vector2T
{
private:

public:
	T _x, _y;
	Vector2T() : _x(0), _y(0) { }
	Vector2T(const Vector2T& newVector2i) :_x(newVector2i._x), _y(newVector2i._y) {}
	Vector2T(const T x, T  y) :_x(x), _y(y) { }

	//rvalue op with vector
	Vector2T operator + (const Vector2T& vector)
	{
		return Vector2T(vector._x + this->_x, vector._y + this->_y);
	}

	Vector2T operator - (const Vector2T& vector)
	{
		return Vector2T(this->_x - vector._x, this->_y - vector._y );
	}

	Vector2T operator * (const Vector2T& vector)
	{
		return Vector2T(vector._x * this->_x, vector._y * this->_y);
	}

	Vector2T operator / (const Vector2T& vector)
	{
		return Vector2T(vector._x / this->_x, vector._y / this->_y);
	}

	//rvalue op with value

	Vector2T operator + (const T& value)
	{
		return Vector2T(this->_x + value, this->_y + value);
	}

	Vector2T operator - (const T& value)
	{
		return Vector2T(this->_x - value, this->_y - value);
	}

	Vector2T operator * (const T& value)
	{
		return Vector2T(this->_x * value, this->_y * value);
	}

	Vector2T operator / (const T& value)
	{
		return Vector2T(this->_x / value, this->_y / value);
	}

	//lvalue op with vector
	Vector2T& operator += (const Vector2T& vector)
	{
		this->_x += vector._x;
		this->_y += vector._y;

		return *this;
	}

	Vector2T& operator -= (const Vector2T& vector)
	{
		this->_x -= vector._x;
		this->_y -= vector._y;

		return *this;
	}

	Vector2T& operator *= (const Vector2T& vector)
	{
		this->_x *= vector._x;
		this->_y *= vector._y;

		return *this;
	}

	Vector2T& operator /= (const Vector2T& vector)
	{
		this->_x /= vector._x;
		this->_y /= vector._y;

		return *this;
	}

	//lvalue op with value
	Vector2T& operator += (const T& value)
	{
		this->_x += value;
		this->_y += value;

		return *this;
	}

	Vector2T& operator -= (const T& value)
	{
		this->_x -= value;
		this->_y -= value;

		return *this;
	}

	Vector2T& operator *= (const T& value)
	{
		this->_x *= value;
		this->_y *= value;

		return *this;
	}

	Vector2T& operator /= (const T& value)
	{
		this->_x /= value;
		this->_y /= value;

		return *this;
	}

	//compare
	bool operator == (const Vector2T<T>& vector)
	{
		return (this->_x == vector._x && this->_y == vector._y);
	}

	bool operator != (const Vector2T<T>& vector)
	{
		return (this->_x != vector._x && this->_y != vector._y);
	}

	bool operator != ( T value)
	{
		return (this->_x != 0 && this->_y != 0);
	}


	//getters and setters
	T getX()const
	{
		return _x;
	}
	void setX(const T& x)
	{
		_x = x;
	}
	T getY()const
	{
		return _y;
	}
	void setY(const T& y)
	{
		_y = y;
	}

	//print 

	const std::string strVector2f() const
	{
		return "(" + std::to_string(_x) + "," + std::to_string(_y) + ")";
	}


	friend std::ostream& operator << (std::ostream& os, const Vector2T& vector)
	{
		os << vector.strVector2f() << "\n";
		return os;
	}

	//formulas
	const double mag() 
	{
		return sqrt(this->_x * this->_x + this->_y * this->_y);
	}

	Vector2T norm()
	{
		Vector2T newVector = *this;
		return newVector / newVector.mag();
	}

};


