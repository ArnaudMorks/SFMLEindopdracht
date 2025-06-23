#include "Enemy.h"

void Enemy::initializeVariables()
{
	this->currentVelocityEnemy.x = 0.f;

	this->movingDirection = 3;	//"0" = links, "1" = rechts, "2" is stoppen, "3" is NIET veranderen van huidige richting (basis)

	this->wallHit = false;

	this->currentDirection = 0;	//"0" = links, "1" = rechts

	this->enemySpawned = false;

	bodyEnemy.currentPosition = Vector2D(0,0);
	rigidBodyEnemy.initializeVariables(massEnemy, forceEnemy, maxVelocityEnemy);

}

void Enemy::initializeShape()
{
	this->enemyShape.setPosition(10.f, 10.f);
	this->enemyShape.setSize(sf::Vector2f(this->visualXYSizePlayer, this->visualXYSizePlayer));
	this->enemyShape.setScale(sf::Vector2f(collisionSizeEnemy.x, collisionSizeEnemy.y));
	this->enemyShape.setFillColor(sf::Color(0, 255, 255));
	this->enemyShape.setOrigin(sf::Vector2f(this->visualXYSizePlayer * 0.5f, 0.f));	//positie in het midden (voor collision)

}

bool Enemy::hasEnemySpawnedCheck()
{
	return this->enemySpawned;
}

void Enemy::enemySpawn(float randomXPosition)
{
	this->enemySpawned = true;
	this->currentVelocityEnemy = Vector2D(0.f, 0.f);
	bodyEnemy.currentPosition = Vector2D(randomXPosition, this->yPositionSpawn);

	this->enemyShape.setPosition(randomXPosition, this->yPositionSpawn);
	this->movingDirection = rand() % 2;		//random kant

	this->enemyShape.setFillColor(sf::Color::Yellow);
}

void Enemy::enemyDespawn()
{
	this->enemySpawned = false;
	this->addPoint();
}

int Enemy::addPoint()
{
	return 1;
}

sf::RectangleShape Enemy::getEnemyShape()
{
	return this->enemyShape;
}

Enemy::Enemy()
{
	initializeVariables();
	initializeShape();
}

Enemy::~Enemy()
{

}

void Enemy::updateMovement()
{
	if (this->movingDirection == 0)	//Left
	{
		if (this->wallHit == true)
		{
			this->movingDirection = 1;
		}

		this->currentVelocityEnemy = rigidBodyEnemy.moveDirectionSpeed(this->currentVelocityEnemy, this->movingDirection);

		bodyEnemy.currentPosition += this->currentVelocityEnemy;

		this->enemyShape.setPosition(bodyEnemy.currentPosition.x, bodyEnemy.currentPosition.y);


		if (this->wallHit == true)
			this->wallHit = false;
		else
		{
			int chanceToChangeDirection;
			chanceToChangeDirection = rand() % randomChangeDirection;
			if (chanceToChangeDirection == 1)
			{
				this->movingDirection = 1;
			}
		}
	}
	else if (this->movingDirection == 1)	//Right
	{
		if (this->wallHit == true)
		{
			this->movingDirection = 0;
		}

		this->currentVelocityEnemy = rigidBodyEnemy.moveDirectionSpeed(this->currentVelocityEnemy, this->movingDirection);

		bodyEnemy.currentPosition += this->currentVelocityEnemy;

		this->enemyShape.setPosition(bodyEnemy.currentPosition.x, bodyEnemy.currentPosition.y);

		if (this->wallHit == true)
			this->wallHit = false;
		else
		{
			int chanceToChangeDirection;
			chanceToChangeDirection = rand() % randomChangeDirection;
			if (chanceToChangeDirection == 0)
			{
				this->movingDirection = 0;
			}
		}
	}

}


void Enemy::updateWindowBoundsCollision()
{
	//Left
	if (bodyEnemy.currentPosition.x - collisionSizeEnemy.x * 0.5f <= 0.f)	//most left side of the screen
	{
		this->wallHit = true;
		int slipDirection = 0;
		this->currentVelocityEnemy.x = rigidBodyEnemy.bounceAgainstWall(this->currentVelocityEnemy, slipDirection);

		bodyEnemy.currentPosition.x += this->currentVelocityEnemy.x;
		bodyEnemy.currentPosition.y += this->currentVelocityEnemy.y;

	}//Right
	else if (bodyEnemy.currentPosition.x + collisionSizeEnemy.x * 0.5f > 1920.f)	//most right side of the screen
	{
		this->wallHit = true;
		int slipDirection = 1;
		this->currentVelocityEnemy.x = rigidBodyEnemy.bounceAgainstWall(this->currentVelocityEnemy, slipDirection);

		bodyEnemy.currentPosition.x += this->currentVelocityEnemy.x;
		bodyEnemy.currentPosition.y += this->currentVelocityEnemy.y;
	}
	else
		this->wallHit = false;

}


void Enemy::update()
{
	if (enemySpawned == false)
		return;

	updateWindowBoundsCollision();

	updateMovement();

}

void Enemy::render(sf::RenderTarget* target)
{
	if (enemySpawned)
		if (target != NULL)
			target->draw(this->enemyShape);
}
