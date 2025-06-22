#include "Player.h"

void Player::initializeVariables()
{
	this->textureRectPlayerPositionXYSize = 16;
	this->spritePlayerXYSize = 10.f;		//"spritePlayerXYSize" bepaalt "shapePlayerXYSize" omdat "spritePlayerXYSize" altijd groter moet zijn
	//Oud systeem om grootte van "sprite" en "shape" gelijk te maken
	//this->shapePlayerXYSize = spritePlayerXYSize * textureRectPlayerPositionXYSize;	//"float * int" converts "int" to float
	this->shapePlayerXYSize = 64.f;

	//PlayerRigidBodyVariables
	//this->forcePlayer.x = 140.f;
	bodyPlayer.forceObject = this->forcePlayer;
	this->massPlayer = 5.f;
	this->currentVelocityPlayer.x = 0.f;
	//this->maxVelocityPlayer.x = 30.f;

	this->wallHit = false;

	this->currentDirection = 0;	//"0" = links, "1" = rechts
	this->currentSpriteMoveFrame = 0;
	//Timer
	this->changeSpriteAnimationMaxTimer = 10.f;		//delta time maybe later
	this->changeSpriteAnimationTimer = this->changeSpriteAnimationTimer;

	this->currentAntiJitterPosition = 0;

	for (int i = 0; i < 3; i++)
	{
		this->antiJitterVectorArray.push_back(i);		//float to int
		std::cout << antiJitterVectorArray[i] << std::endl;
	}

	startPositionPlayer = Vector2D(800, 900);
	//startPositionPlayer = Vector2D(800, 0);

	bodyPlayer.currentPosition = startPositionPlayer;
	rigidBodyPlayer.initializeVariables(massPlayer, bodyPlayer.forceObject, maxVelocityPlayer);
}

void Player::initializeSprite()
{
	this->playerTexture.loadFromFile("images/SnowManSpriteSheet.png");
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setTextureRect(sf::IntRect(0, 0, textureRectPlayerPositionXYSize,
		textureRectPlayerPositionXYSize));		//pak deel van sprite-sheet
	this->playerSprite.setScale(spritePlayerXYSize, spritePlayerXYSize);
	this->playerSprite.setOrigin(sf::Vector2f(textureRectPlayerPositionXYSize * 0.5f, 0.f));	//positie in het midden (voor "mirror" in animatie)
}

void Player::initializeShape()
{
	this->playerShape.setFillColor(sf::Color::Blue);
	this->playerShape.setSize(sf::Vector2f(shapePlayerXYSize, shapePlayerXYSize));
	//Oude versie voor als "shape" net zo groot is als "sprite"
	//this->playerShape.setOrigin(sf::Vector2f(shapePlayerXYSize * 0.5f, 0.f));
	this->playerShape.setOrigin(sf::Vector2f(32.f, -40.f));
}


Player::Player(float x, float y)
{
	this->shapeAndSpritePosition(startPositionPlayer.x, startPositionPlayer.y);

	this->initializeVariables();
	this->initializeSprite();
	this->initializeShape();
}

Player::~Player()
{

}

void Player::shapeAndSpritePosition(float x, float y)
{
	this->playerShape.setPosition(x, y);
	this->playerSprite.setPosition(x, y);
}

void Player::directionChangeSprite(int movingDirection)
{
	if (movingDirection != this->currentDirection && movingDirection != 3)	//"2" = niet van richting verandert
	{
		if (movingDirection == 0)
			this->playerSprite.setScale(this->spritePlayerXYSize, this->spritePlayerXYSize);
		else //altijd "if (movingDirection == 1)"
			this->playerSprite.setScale(-this->spritePlayerXYSize, this->spritePlayerXYSize);
		this->currentDirection = movingDirection;
	}
}

const sf::RectangleShape& Player::getPlayerShape() const
{
	return this->playerShape;
}


void Player::updateSprite(bool moving)		//animation and movingDirection
{
	if (moving)
	{
		if (this->changeSpriteAnimationTimer >= this->changeSpriteAnimationMaxTimer)
		{
			if (this->currentSpriteMoveFrame == 0)
			{
				this->playerSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
				this->currentSpriteMoveFrame = 1;
			}
			else
			{
				this->playerSprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
				this->currentSpriteMoveFrame = 0;
			}
			this->changeSpriteAnimationTimer = 0.f;
		}
		else
			this->changeSpriteAnimationTimer += 1.f;		//timer increase
	}
	else
	{
		this->playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		this->changeSpriteAnimationTimer = this->changeSpriteAnimationMaxTimer;	//als je stil staat begint de animatie instantly als je weer beweegt
	}
}

void Player::updateInput()
{
	int movingDirection = 3;		//"0" = links, "1" = rechts, "2" is stoppen, "3" is NIET veranderen van huidige richting (basis)
	int visualMoveDirection = 3;	//alleen voor sprite direction
	bool moving = false;			


	//Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)			//No move
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moving = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	//Left
	{
		movingDirection = 0;
		visualMoveDirection = movingDirection;

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))	MANUAL WALL COLLISION TEST
		if (this->wallHit == true)
		{
			movingDirection = 1;
		}

		this->currentVelocityPlayer = rigidBodyPlayer.moveDirectionSpeed(this->currentVelocityPlayer, movingDirection);


		//sf::Vector2f currentPosition = this->playerShape.getPosition();//LATER EIGEN VECTOR2D VAN MAKEN!!!

		bodyPlayer.currentPosition.x += this->currentVelocityPlayer.x;
		//this->playerShape.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);
		//this->playerSprite.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);

		moving = true;

		if (this->wallHit == true)
			this->wallHit = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	//Right
	{
		movingDirection = 1;
		visualMoveDirection = movingDirection;

		if (this->wallHit == true)
		{
			movingDirection = 0;
		}

		this->currentVelocityPlayer = rigidBodyPlayer.moveDirectionSpeed(this->currentVelocityPlayer, movingDirection);

		//sf::Vector2f currentPosition = this->playerShape.getPosition();//LATER EIGEN VECTOR2D VAN MAKEN!!!

		bodyPlayer.currentPosition.x += this->currentVelocityPlayer.x;
		//this->playerShape.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);
		//this->playerSprite.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);

		moving = true;

		if (this->wallHit == true)
			this->wallHit = false;
	}
	else
		moving = false;

	if (moving == false)
	{
		//sf::Vector2f currentPosition = this->playerShape.getPosition();
		
		float positionPlusVelocity = (bodyPlayer.currentPosition.x + this->currentVelocityPlayer.x)
			- bodyPlayer.currentPosition.x;

		if (positionPlusVelocity < 0.5f && positionPlusVelocity > -0.5f)
		{
			antiJitterVectorArray[this->currentAntiJitterPosition] = positionPlusVelocity;

			if (this->currentAntiJitterPosition < 2)
				this->currentAntiJitterPosition++;
			else
				this->currentAntiJitterPosition = 0;

			for (int i = 0; i < 3; i++)
			{
				int j;
				int k;

				if (i != 2)
					j = i + 1;
				else
					j = 0;

				if (i != 0)
					k = i - 1;
				else
					k = 2;

				if (this->antiJitterVectorArray[i] == antiJitterVectorArray[j]
					|| this->antiJitterVectorArray[i] == antiJitterVectorArray[k]
					|| this->antiJitterVectorArray[j] == antiJitterVectorArray[k])
				{
					movingDirection = 2;	//don't move
				}

				//std::cout << antiJitterVectorArray[i] << std::endl;
			}
		}

		if (movingDirection != 2)		//"2" = stil staan
		{
			if (positionPlusVelocity < 0.f)	//Links
				movingDirection = 0;
			else if ((positionPlusVelocity > 0.f))	//Rechts
				movingDirection = 1;

			this->currentVelocityPlayer.x = rigidBodyPlayer.moveDirectionStopping(currentVelocityPlayer, movingDirection,
				this->wallHit);
			bodyPlayer.currentPosition.x += this->currentVelocityPlayer.x;

		}
		//std::cout << positionPlusVelocity << std::endl;

		//this->playerShape.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);
		//this->playerSprite.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);
	}

	this->playerSprite.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);
	this->playerShape.setPosition(bodyPlayer.currentPosition.x, bodyPlayer.currentPosition.y);

	this->updateSprite(moving);
	this->directionChangeSprite(visualMoveDirection);

}

void Player::updateWindowBoundsCollision()
{
	//Left
	//sf::Vector2f playerPosition = this->playerShape.getPosition();	//eigen vector2 maken
	if (bodyPlayer.currentPosition.x - collisionSizePlayer.x * 0.5f <= 0.f)
	{
		this->wallHit = true;
		int slipDirection = 0;
		this->currentVelocityPlayer.x = rigidBodyPlayer.bounceAgainstWall(this->currentVelocityPlayer, slipDirection);

		//sf::Vector2f currentPosition = this->playerShape.getPosition();


		bodyPlayer.currentPosition.x += this->currentVelocityPlayer.x;

	}//Right
	else if (bodyPlayer.currentPosition.x + collisionSizePlayer.x * 0.5f >= 1920)
	{
		this->wallHit = true;
		int slipDirection = 1;
		this->currentVelocityPlayer.x = rigidBodyPlayer.bounceAgainstWall(this->currentVelocityPlayer, slipDirection);

		//sf::Vector2f currentPosition = this->playerShape.getPosition();
		bodyPlayer.currentPosition.x += this->currentVelocityPlayer.x;
		//this->playerShape.setPosition(target->getSize().x, playerPosition.y);
	}
	else
		this->wallHit = false;

}

void Player::update()
{
	//Window bounds collision
	this->updateWindowBoundsCollision();

	this->updateInput();

	//std::cout << this->bodyPlayer.currentPosition.x << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	//target->draw(this->playerShape);			//is er om te size te berekenen; moet onzichtbaar zijn; uitcommenten voor testen
	target->draw(this->playerSprite);
}

