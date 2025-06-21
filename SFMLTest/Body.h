#pragma once

#include "RigidBody2D.h"

class Body
{
private:
	Vector2D const screenCenter = Vector2D(0, 0);
	void initializeVariablesBody();
public:
	Vector2D currentPosition;
};

