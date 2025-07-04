#include "RigidBody2D.h"


void RigidBody2D::initializeVariables(float mass, Vector2D ownForce, Vector2D maxVelocity)
{
	this->mass = mass;
	this->ownForce.x = ownForce.x;

	//Friction force berekenen; weerstand, en massa acceleratie
	this->Fw = this->mass * this->gravity;
	this->FN = -this->Fw;
	this->fF = this->Mu * this->FN;

	//X
	if ((this->ownForce.x - this->fF) > 0)
	{
		this->mA = this->ownForce.x - this->fF;	//massa acceleratie
		this->acceleration.x = this->mA / this->mass * deltaTime;
	}
	else
	{
		mA = 0;
		acceleration.x = 0;
	}

	//Y
	if ((this->ownForce.y - this->fF) > 0)
	{
		this->mA = this->ownForce.y - this->fF;	//massa acceleratie
		this->acceleration.y = this->mA / this->mass * deltaTime;
	}
	else
	{
		mA = 0;
		acceleration.y = 0;
	}

	this->maxVelocity = maxVelocity;

	this->moveDirectionX = 0;
}

RigidBody2D::RigidBody2D()
{
	initializeVariables(1.f, Vector2D(1.f, 1.f), Vector2D(1.f, 1.f));
}


Vector2D RigidBody2D::moveDirectionSpeed(Vector2D currentVelocity, int direction)		//beweeg met "ownForce" tegen "frictie ownForce"	returned "speed"
{
	this->currentVelocity.x = currentVelocity.x;		//IN DE MIN ALS JE NAAR LINKS GAAT
	this->moveDirectionX = direction;


	if (this->moveDirectionX == 0)
	{
		if (this->currentVelocity.x > -maxVelocity.x)
			this->currentVelocity.x -= acceleration.x;
		else
			this->currentVelocity.x = -maxVelocity.x;
	}
	else if (this->moveDirectionX == 1)
	{
		if (this->currentVelocity.x < maxVelocity.x)
		{
			this->currentVelocity.x += acceleration.x;
		}
		else
			this->currentVelocity.x = maxVelocity.x;
	}

	if (this->maxVelocity.y != 0)		// "0" = "maxVelocity.y" for the player
		if (this->currentVelocity.y < maxVelocity.y)
			this->currentVelocity.y += acceleration.y;
		else
			this->currentVelocity.y = maxVelocity.y;

	return this->currentVelocity;
}


float RigidBody2D::moveDirectionStopping(Vector2D currentVelocity, int movingDirection, int wallHit)		//beweeg met "ownForce" tegen "frictie ownForce"	returned "speed"
{
	this->moveDirectionX = movingDirection;
	this->currentVelocity = currentVelocity;


	if (this->moveDirectionX == 0 && this->currentVelocity.x < 0)
	{
		if ((this->currentVelocity.x + this->acceleration.x && wallHit == false) < 0.f)		//zorgt ervoor dat acceleratie niet constant heen en weer gaat
			this->currentVelocity.x = 0.f;
		else if (wallHit == false)
			this->currentVelocity.x += this->acceleration.x;
	}
	else if (this->moveDirectionX == 1 && this->currentVelocity.x > 0)
	{
		if ((this->currentVelocity.x + this->acceleration.x && wallHit == false) < 0.f)	//UNSAFE BOOL IN OPERATION; weet niet hoe ik het kan laten werken als ik het verander
			this->currentVelocity.x = 0.f;
		else if (wallHit == false)
			this->currentVelocity.x -= this->acceleration.x;
	}
	


	return this->currentVelocity.x;
}


float RigidBody2D::bounceAgainstWall(Vector2D currentVelocity, int slipDircetion)
{
	this->moveDirectionX = slipDircetion;

	if ((this->currentVelocity.x < 0 && slipDircetion == 0) || (this->currentVelocity.x > 0 && slipDircetion == 1))
		this->currentVelocity.x = -this->currentVelocity.x * (1.f - this->forceLostOnBounce);

	return this->currentVelocity.x;
}

