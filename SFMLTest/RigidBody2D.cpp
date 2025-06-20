#include "RigidBody2D.h"
//test

void RigidBody2D::initializeVariables(float mass, float ownForce, float maxVelocity)
{
	this->mass = mass;
	this->ownForce = ownForce;

	//Friction force berekenen; weerstand, en massa acceleratie
	this->Fw = this->mass * this->gravity;
	this->FN = -this->Fw;
	this->fF = this->Mu * this->FN;

	if ((this->ownForce - this->fF) > 0)
	{
		this->mA = this->ownForce - this->fF;	//massa acceleratie
		this->acceleration = this->mA / this->mass * 0.0167f;	//framerate = "60", dus "* 0.0167f"
	}
	else
	{
		mA = 0;
		acceleration = 0;
	}
	this->netForce = this->ownForce - this->fF;

	///*TEST acceleration*/ this->acceleration = 1.f;
	this->maxVelocity = maxVelocity;
	//this->maxVelocity = 

	moveDirectionX = 0;
}

RigidBody2D::RigidBody2D()
{
	initializeVariables(1.f, 1.f, 1.f);
}


float RigidBody2D::moveDirectionSpeed(float currentVelocity, int direction)		//beweeg met "ownForce" tegen "frictie ownForce"	returned "speed"
{
	this->currentVelocity = currentVelocity;		//IN DE MIN ALS JE NAAR LINKS GAAT
	this->moveDirectionX = direction;

	/*std::cout << this->mass << std::endl;
	std::cout << this->ownForce << std::endl;			//DEBUGGING
	std::cout << this->acceleration << std::endl;*/

	if (this->moveDirectionX == 0)
	{
		if (this->currentVelocity > -maxVelocity)
			this->currentVelocity -= acceleration;
		else
			this->currentVelocity = -maxVelocity;
	}
	else if (this->moveDirectionX == 1)
	{
		if (this->currentVelocity < maxVelocity)
		{
			this->currentVelocity += acceleration;
		}
		else
			this->currentVelocity = maxVelocity;
	}


	/*if (this->ownForce > this->fF)
	{
		this->netForce = this->ownForce - this->fF;

		this->acceleration = this->netForce / this->mass;
	}
	else	//als "ownForce" minder is dan "frictie ownForce" dan is acceleratie "0", waardoor "velocity" constant is
	{
		this->acceleration = 0;
	}*/															//Later pas nuttig; als er "drag" bij wordt toegevoegt

	return this->currentVelocity;
}

float RigidBody2D::moveDirectionStopping(float currentVelocity, int movingDirection, int wallHit)		//beweeg met "ownForce" tegen "frictie ownForce"	returned "speed"
{
	this->moveDirectionX = movingDirection;
	this->currentVelocity = currentVelocity;


	if (this->moveDirectionX == 0 && this->currentVelocity < 0)
	{
		if ((this->currentVelocity + this->acceleration && wallHit == false) < 0.f)		//zorgt ervoor dat acceleratie niet constant heen en weer gaat
			this->currentVelocity = 0.f;
		else if (wallHit == false)
			this->currentVelocity += this->acceleration;
	}
	else if (this->moveDirectionX == 1 && this->currentVelocity > 0)
	{
		if ((this->currentVelocity + this->acceleration && wallHit == false) < 0.f)	//UNSAFE BOOL IN OPERATION; weet niet hoe ik het kan laten werken als ik het verander
			this->currentVelocity = 0.f;
		else if (wallHit == false)
			this->currentVelocity -= this->acceleration;
	}
	


	return this->currentVelocity;
}


float RigidBody2D::bounceAgainstWall(float currentVelocity, int slipDircetion)
{
	this->moveDirectionX = slipDircetion;

	if (this->currentVelocity < 0 && slipDircetion == 0)
		this->currentVelocity = -this->currentVelocity * (1.f - 0.15f);		//"0.15f" = force lost bij stuiteren tegen de muur
	else if (this->currentVelocity > 0 && slipDircetion == 1)
		this->currentVelocity = -this->currentVelocity * (1.f - 0.15f);		//"0.15f" = force lost bij stuiteren tegen de muur


	return this->currentVelocity;
}

