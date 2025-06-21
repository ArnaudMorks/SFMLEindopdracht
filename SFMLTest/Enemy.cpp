#include "Enemy.h"

void Enemy::initializeVariables()
{
	//this->textureRectEnemyPositionXYSize = 16;
	//this->spriteEnemyXYSize = 4.f;		//"spritePlayerXYSize" bepaalt "shapePlayerXYSize" omdat "spritePlayerXYSize" altijd groter moet zijn
	this->shapeEnemyXYSize = 0.5f;	//"float * int" converts "int" to float

	//PlayerRigidBodyVariables
	this->forceEnemy.x = 20.f;
	this->massEnemy = 2.f;
	this->currentVelocityEnemy.x = 0.f;
	this->maxVelocityEnemy.x = 30.f;

	this->movingDirection = 3;		//"0" = links, "1" = rechts, "2" is stoppen, "3" is NIET veranderen van huidige richting (basis)

	this->wallHit = false;

	this->currentDirection = 0;	//"0" = links, "1" = rechts

	this->enemySpawned = false;

	rigidBodyEnemy.initializeVariables(massEnemy, forceEnemy, maxVelocityEnemy);

}

void Enemy::initializeShape()
{
	this->enemyShape.setPosition(10.f, 10.f);
	this->enemyShape.setSize(sf::Vector2f(100.f, 100.f));
	this->enemyShape.setScale(sf::Vector2f(shapeEnemyXYSize, shapeEnemyXYSize));
	this->enemyShape.setFillColor(sf::Color(0, 255, 255));
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
	//"rand" pakt alleen een "int", "static_cast" maakt op het laatst weer een "float"
	this->enemyShape.setPosition(randomXPosition, -100.f);
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

		this->currentVelocityEnemy.x = rigidBodyEnemy.moveDirectionSpeed(this->currentVelocityEnemy, this->movingDirection);


		sf::Vector2f currentPosition = this->enemyShape.getPosition();
		currentPosition.x += this->currentVelocityEnemy.x;
		if (currentVelocityEnemy.y > 0)	//maakt het direction onafhankelijk (moet beter later)
			currentPosition.y += this->currentVelocityEnemy.y;
		else
			currentPosition.y -= this->currentVelocityEnemy.y;
		this->enemyShape.setPosition(currentPosition);
		//this->playerSprite.setPosition(currentPosition);


		if (this->wallHit == true)
			this->wallHit = false;
	}
	else if (this->movingDirection == 1)	//Right
	{
	//visualMoveDirection = movingDirection;

	if (this->wallHit == true)
	{
		this->movingDirection = 0;
	}

	this->currentVelocityEnemy.y = rigidBodyEnemy.moveDirectionSpeed(this->currentVelocityEnemy, this->movingDirection);


	sf::Vector2f currentPosition = this->enemyShape.getPosition();
	currentPosition.x += this->currentVelocityEnemy.x;
	if (currentVelocityEnemy.y > 0)	//maakt het direction onafhankelijk (moet beter later)
		currentPosition.y += this->currentVelocityEnemy.y;
	else
		currentPosition.y -= this->currentVelocityEnemy.y;
	this->enemyShape.setPosition(currentPosition);
	//this->playerSprite.setPosition(currentPosition);


	if (this->wallHit == true)
		this->wallHit = false;
	}
}


void Enemy::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	sf::Vector2f playerPosition = this->enemyShape.getPosition();	//eigen vector2 maken
	if (this->enemyShape.getGlobalBounds().left <= 0.f)
	{
		this->wallHit = true;
		int slipDirection = 0;
		this->currentVelocityEnemy.x = rigidBodyEnemy.bounceAgainstWall(this->currentVelocityEnemy, slipDirection);

		sf::Vector2f currentPosition = this->enemyShape.getPosition();
		//std::cout << currentPosition.x << std::endl;
		currentPosition.x += this->currentVelocityEnemy.x;
		currentPosition.y += this->currentVelocityEnemy.y;
		//std::cout << currentPosition.x << std::endl;
	}//Right
	else if (this->enemyShape.getGlobalBounds().left + this->enemyShape.getGlobalBounds().width >= target->getSize().x)
	{
		this->wallHit = true;
		int slipDirection = 1;
		this->currentVelocityEnemy.x = rigidBodyEnemy.bounceAgainstWall(this->currentVelocityEnemy, slipDirection);

		sf::Vector2f currentPosition = this->enemyShape.getPosition();
		currentPosition.x += this->currentVelocityEnemy.x;
		currentPosition.y += this->currentVelocityEnemy.y;
	}
	else
		this->wallHit = false;

}


void Enemy::update(const sf::RenderTarget* target)
{
	if (enemySpawned == false)
		return;

	updateWindowBoundsCollision(target);

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
		target->draw(this->enemyShape);
}
