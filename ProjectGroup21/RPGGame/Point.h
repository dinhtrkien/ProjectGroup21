#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point
{
public:
	float x;
	float y;

	Point();
	Point(float x, float y);

	Point& Add(const Point& p);
	Point& Subtract(const Point& p);
	Point& Multiply(const Point& p);
	Point& Devide(const Point& p);

	friend Point& operator+(Point& p1, const Point& p2);
	friend Point& operator-(Point& p1, const Point& p2);
	friend Point& operator*(Point& p1, const Point& p2);
	friend Point& operator/(Point& p1, const Point& p2);

	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(const Point& p);
	Point& operator/=(const Point& p);

	Point& operator*(const float& i);
	Point& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Point& p);
};



#endif // POINT_H_

