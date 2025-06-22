#pragma once

#include "RigidBody2D.h"
#include "Body.h"

class Player
{
private:
	int textureRectPlayerPositionXYSize;
	float spritePlayerXYSize;		//van spritesheet; grootte per plaatje is 16x16
	float shapePlayerXYSize;		//hitbox. "setScale" en "setSize" zijn floats
	float massPlayer;
	const Vector2D forcePlayer = Vector2D(140.f, 0.f);
	Vector2D currentVelocityPlayer;
	const Vector2D maxVelocityPlayer = Vector2D(30.f, 0.f);

	bool wallHit;

	int currentDirection;
	int currentSpriteMoveFrame;		//tussen "0" en "1" is loop animatie
	float changeSpriteAnimationMaxTimer;
	float changeSpriteAnimationTimer;

	int currentAntiJitterPosition;
	std::vector<float> antiJitterVectorArray;

	Vector2D startPositionPlayer;

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::RectangleShape playerShape;

	RigidBody2D rigidBodyPlayer;

	//Private Functions
	void shapeAndSpritePosition(float x, float y);
	void initializeVariables();
	void initializeShape();
	void initializeSprite();
	void directionChangeSprite(int direction = 0.f);	//zit in "updateInput" om richting te bepalen
	void updateSprite(bool moving = false);		//zit in "updateInput" om de animatie te bepalen

public:
	Player(float x = 0.f, float y = 0.f);		//parameters zijn om positie mee te geven, values om default position mee te geven
	virtual ~Player();

	const Vector2D collisionSizePlayer = Vector2D(64, 80);
	Body bodyPlayer;
	const sf::RectangleShape& getPlayerShape() const;

	//Public Functions
	void updateInput();
	void updateWindowBoundsCollision();
	void update();
	void render(sf::RenderTarget* target);
	//void renderPlayer();
};

