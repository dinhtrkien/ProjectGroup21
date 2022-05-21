#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& v);
	Vector2D& Subtract(const Vector2D& v);
	Vector2D& Multiply(const Vector2D& v);
	Vector2D& Devide(const Vector2D& v);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator/=(const Vector2D& v);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& v);
};



#endif // VECTOR2D_H_
