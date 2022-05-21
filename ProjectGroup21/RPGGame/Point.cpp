#include "Point.h"

Point::Point()
{
	x = 0.0f;
	y = 0.0f;
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point& Point::Add(const Point& p)
{
	this->x += p.x;
	this->y += p.y;

	return *this;
}

Point& Point::Subtract(const Point& p)
{
	this->x -= p.x;
	this->y -= p.y;

	return *this;
}

Point& Point::Multiply(const Point& p)
{
	this->x *= p.x;
	this->y *= p.y;

	return *this;
}

Point& Point::Devide(const Point& p)
{
	this->x /= p.x;
	this->y /= p.y;

	return *this;
}

Point& operator+(Point& p1, const Point& p2)
{
	return p1.Add(p2);
}

Point& operator-(Point& p1, const Point& p2)
{
	return p1.Subtract(p2);
}

Point& operator*(Point& p1, const Point& p2)
{
	return p1.Multiply(p2);
}

Point& operator/(Point& p1, const Point& p2)
{
	return p1.Devide(p2);
}

Point& Point::operator+=(const Point& p)
{
	return this->Add(p);
}

Point& Point::operator-=(const Point& p)
{
	return this->Subtract(p);
}

Point& Point::operator*=(const Point& p)
{
	return this->Multiply(p);
}

Point& Point::operator/=(const Point& p)
{
	return this->Devide(p);
}

Point& Point::operator*(const float& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}
Point& Point::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Point& p)
{
	stream << "(" << p.x << "," << p.y << ")";
	return stream;
}