#pragma once
class Vector2D
{
public:
	float x;
	float y;

	Vector2D();	//default constructor
	Vector2D(float x, float y) : x(x), y(y) {};

	Vector2D& Subtract(const Vector2D& vector);

	float Magnitude() const;

	Vector2D& operator+=(const Vector2D& vector);

};

