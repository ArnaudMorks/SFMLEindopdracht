#pragma once

#include "RigidBody2D.h"
#include "Body.h"

class Enemy
{
private:
	const float visualXYSizePlayer = 100.f;
	const float massEnemy = 2.f;
	const float yPositionSpawn = -100.f;

	const int randomChangeDirection = 600;	//determines how bit the chance is to change direction (per frame)

	const Vector2D forceEnemy = Vector2D(40.f, 4.f);
	Vector2D currentVelocityEnemy;
	const Vector2D maxVelocityEnemy = Vector2D(50.f, 9.f);

	int movingDirection;

	bool wallHit;

	bool enemySpawned;

	int currentDirection;

	sf::RectangleShape enemyShape;

	RigidBody2D rigidBodyEnemy;

	//Private functions
	void initializeVariables();
	void initializeShape();

public:
	Enemy();
	virtual ~Enemy();

	const Vector2D collisionSizeEnemy = Vector2D(0.5f, 0.5f);
	Body bodyEnemy;

	//Public Functions
	void enemyDespawn();
	int addPoint();
	sf::RectangleShape getEnemyShape();
	bool hasEnemySpawnedCheck();
	void enemySpawn(float randomXPosition);
	void updateMovement();
	void updateWindowBoundsCollision();
	void update();
	void render(sf::RenderTarget* target);

};

