#include "Enemy.h"

void Enemy::initializeVariables()
{
	//this->textureRectEnemyPositionXYSize = 16;
	//this->spriteEnemyXYSize = 4.f;		//"spritePlayerXYSize" bepaalt "shapePlayerXYSize" omdat "spritePlayerXYSize" altijd groter moet zijn
	//this->shapeEnemyXYSize = 0.5f;	//"float * int" converts "int" to float

	//PlayerRigidBodyVariables
	//this->forceEnemy = Vector2D(20.f, 1.f);
	//this->massEnemy = 2.f;
	this->currentVelocityEnemy.x = 0.f;
	//this->maxVelocityEnemy.x = 30.f;

	this->movingDirection = 3;		//"0" = links, "1" = rechts, "2" is stoppen, "3" is NIET veranderen van huidige richting (basis)

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
	//std::cout << enemySpawned << std::endl;
	this->currentVelocityEnemy = Vector2D(0.f, 0.f);
	bodyEnemy.currentPosition = Vector2D(randomXPosition, this->yPositionSpawn);
	//"rand" pakt alleen een "int", "static_cast" maakt op het laatst weer een "float"
	this->enemyShape.setPosition(randomXPosition, this->yPositionSpawn);
	this->movingDirection = rand() % 2;		//random kant
	//std::cout << movingDirection << std::endl;

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
		//visualMoveDirection = movingDirection;

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))	MANUAL WALL COLLISION TEST
		if (this->wallHit == true)
		{
			this->movingDirection = 1;
		}

		this->currentVelocityEnemy = rigidBodyEnemy.moveDirectionSpeed(this->currentVelocityEnemy, this->movingDirection);
		//this->currentVelocityEnemy.y = rigidBodyEnemy.enemyMoveDownSpeed(this->currentVelocityEnemy.y);

		//sf::Vector2f currentPosition = this->enemyShape.getPosition();
		bodyEnemy.currentPosition += this->currentVelocityEnemy;
		/*if (currentVelocityEnemy.y > 0)	//maakt het direction onafhankelijk (moet beter later)
			bodyEnemy.currentPosition.y += this->currentVelocityEnemy.y;
		else
			bodyEnemy.currentPosition.y -= this->currentVelocityEnemy.y;*/
		this->enemyShape.setPosition(bodyEnemy.currentPosition.x, bodyEnemy.currentPosition.y);
		//this->playerSprite.setPosition(currentPosition);


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
		//visualMoveDirection = movingDirection;

		if (this->wallHit == true)
		{
			this->movingDirection = 0;
		}

		this->currentVelocityEnemy = rigidBodyEnemy.moveDirectionSpeed(this->currentVelocityEnemy, this->movingDirection);
		//this->currentVelocityEnemy.y = rigidBodyEnemy.enemyMoveDownSpeed(this->currentVelocityEnemy.y);

		//sf::Vector2f currentPosition = this->enemyShape.getPosition();
		bodyEnemy.currentPosition += this->currentVelocityEnemy;
		/*if (currentVelocityEnemy.y > 0)	//maakt het direction onafhankelijk (moet beter later)
			bodyEnemy.currentPosition.y += this->currentVelocityEnemy.y;
		else
			bodyEnemy.currentPosition.y -= this->currentVelocityEnemy.y;*/
		this->enemyShape.setPosition(bodyEnemy.currentPosition.x, bodyEnemy.currentPosition.y);
		//this->playerSprite.setPosition(currentPosition);


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

	//bodyEnemy.currentPosition.y += 1.f;

	//std::cout << bodyEnemy.currentPosition.x << std::endl;
}


void Enemy::updateWindowBoundsCollision()
{
	//Left
	//sf::Vector2f playerPosition = this->enemyShape.getPosition();	//eigen vector2 maken
	if (bodyEnemy.currentPosition.x - collisionSizeEnemy.x * 0.5f <= 0.f)	//most left side of the screen
	{
		//std::cout << bodyEnemy.currentPosition.x << std::endl;
		this->wallHit = true;
		int slipDirection = 0;
		this->currentVelocityEnemy.x = rigidBodyEnemy.bounceAgainstWall(this->currentVelocityEnemy, slipDirection);

		//sf::Vector2f currentPosition = this->enemyShape.getPosition();
		//std::cout << currentPosition.x << std::endl;
		bodyEnemy.currentPosition.x += this->currentVelocityEnemy.x;
		bodyEnemy.currentPosition.y += this->currentVelocityEnemy.y;
		//std::cout << currentPosition.x << std::endl;
	}//Right
	else if (bodyEnemy.currentPosition.x + collisionSizeEnemy.x * 0.5f > 1920.f)	//most right side of the screen
	{
		this->wallHit = true;
		int slipDirection = 1;
		this->currentVelocityEnemy.x = rigidBodyEnemy.bounceAgainstWall(this->currentVelocityEnemy, slipDirection);

		//sf::Vector2f currentPosition = this->enemyShape.getPosition();
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

	/*//Remove enemy past the bottom		WORDT VANUIT "Game" gedaan
	if (this->enemyShape.getPosition().y > target->getSize().y)
	{
		this->enemyDespawn();
		std::cout << this->enemyShape.getPosition().y << "Enemy Despawned" << std::endl;
	}*/
}

void Enemy::render(sf::RenderTarget* target)
{
	if (enemySpawned)
		if (target != NULL)
			target->draw(this->enemyShape);
}
