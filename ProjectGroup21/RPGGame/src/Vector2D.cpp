#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& v)
{
	this->x += v.x;
	this->y += v.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& v)
{
	this->x -= v.x;
	this->y -= v.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& v)
{
	this->x *= v.x;
	this->y *= v.y;

	return *this;
}

Vector2D& Vector2D::Devide(const Vector2D& v)
{
	this->x /= v.x;
	this->y /= v.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Devide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	return this->Add(v);
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	return this->Subtract(v);
}

Vector2D& Vector2D::operator*=(const Vector2D& v)
{
	return this->Multiply(v);
}

Vector2D& Vector2D::operator/=(const Vector2D& v)
{
	return this->Devide(v);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}
Vector2D& Vector2D::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}