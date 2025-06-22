#pragma once

#include "RigidBody2D.h"
#include "Body.h"

class Enemy
{
private:
	int textureRectEnemyPositionXYSize;
	float spriteEnemyXYSize;		//van spritesheet; grootte per plaatje is 16x16
	float shapeEnemyXYSize;		//hitbox. "setScale" en "setSize" zijn floats
	float massEnemy;
	const float yPositionSpawn = -100.f;

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
	//const sf::RectangleShape getEnemyShape() const;		//"const" want wordt nooit verandert

	//Public Functions
	void enemyDespawn();
	int addPoint();
	sf::RectangleShape getEnemyShape();
	bool hasEnemySpawnedCheck();
	void enemySpawn(float randomXPosition);
	void updateMovement();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

