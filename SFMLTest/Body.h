#pragma once

#include "RigidBody2D.h"

class Body
{
private:
	Vector2D const screenCenter = Vector2D(960, 540);	//this because screen size is set to "1920x1080"
	void initializeVariablesBody();
public:
	Body();
	virtual ~Body();

	Vector2D currentPosition;		//saves current location, and used to "set position"
	Vector2D forceObject;			//gets set by a "const" in "Player" and "Enemy"
	Vector2D currentVelocityObject;

	RigidBody2D rigidBody;

};

