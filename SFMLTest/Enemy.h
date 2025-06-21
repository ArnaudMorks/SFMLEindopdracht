#pragma once

#include "RigidBody2D.h"

class Enemy
{
private:
	int textureRectEnemyPositionXYSize;
	float spriteEnemyXYSize;		//van spritesheet; grootte per plaatje is 16x16
	float shapeEnemyXYSize;		//hitbox. "setScale" en "setSize" zijn floats
	Vector2D forceEnemy;
	float massEnemy;
	Vector2D currentVelocityEnemy;
	Vector2D maxVelocityEnemy;

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

	const sf::RectangleShape getEnemyShape() const;		//"const" want wordt nooit verandert

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

