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

