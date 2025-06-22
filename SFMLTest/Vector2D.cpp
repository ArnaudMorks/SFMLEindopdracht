#include "Vector2D.h"

Vector2D::Vector2D()
{

}

/*Vector2D::Vector2D(float x, float y)
{

}*/

Vector2D& Vector2D::Subtract(const Vector2D& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

float Vector2D::Magnitude() const
{
	return x * x + y * y;
}

/*bool Vector2D::operator<(const Vector2D& vector) const
{
	return this->Magnitude() < vector.Magnitude();
}

bool Vector2D::operator>(const Vector2D& vector) const
{
	return this->Magnitude() > vector.Magnitude();
}

bool Vector2D::operator==(const Vector2D& vector) const
{
	return this->Magnitude() == vector.Magnitude();
}


Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}*/

/*bool operator==(const Vector2D& v1, const Vector2D& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}*/


/*Vector2D& Vector2D::operator-(Vector2D& v1, const Vector2D& v2)
{

}*/

/*
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

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
	return v1.Divide(v2);
}*/


