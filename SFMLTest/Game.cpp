#include "Game.h"

//Private functions
void Game::initializeVariables()
{
	this->windowPointer = nullptr;

	//Game logic
	this->points = 0;
	this->enemyMaxSpawnTimer = 200.f;		//delta time maybe later
	this->enemySpawnTimer = this->enemyMaxSpawnTimer;
	this-> timerSpeedUpInterval = 8.f;
	this-> timerSpeedupTimer;

	this->maxEnemies = 30;
	//this->hittable = true;
	//this->mouseHeld = false;
	//this->timeToWin = 80.f;	//tijd in seconden
	//this->timePassed = 0.f;
	this->win = false;
	this->lost = false;




	for (int i = 0; i < maxEnemies; i++)
	{
		this->enemies.push_back(Enemy());		//maak alle enemies; worden "gespawned" en "gedespawned"; vectorArray verandert niet
	}
}

void Game::initializeWindow()
{
	this->videoMode.width = screenSize.x;
	this->videoMode.height = screenSize.y;

	this->windowPointer = new sf::RenderWindow(this->videoMode, "Snowman Dodge",
		sf::Style::Fullscreen | sf::Style::Close);

	if (this->windowPointer != NULL)
		this->windowPointer->setFramerateLimit(this->frameRate);			//FRAME RATE
}

void Game::initializeSprite()
{
	this->winScreenTexture.loadFromFile("images/WinScreen.png");
	this->loseScreenTexture.loadFromFile("images/LoseScreen.png");

	this->endScreenSprite.setTexture(this->loseScreenTexture);
	//this->endScreenSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	this->endScreenSprite.setScale(1, 1);
}

void Game::initializeFonts()
{
	this->font.loadFromFile("Fonts/PlaywriteVN-Regular.ttf");
}

void Game::initializeTexts()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setString("HALLO");
	this->uiText.setPosition(30.f, 30.f);
}


/*void Game::initializeEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color(0, 255, 255));
	//this->enemy.setOutlineColor(sf::Color(255, 0, 0));
	//this->enemy.setOutlineThickness(1.f);		//outline beweegt raar mee
}*/

//Constructors / Destructors
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeSprite();
	this->initializeFonts();
	this->initializeTexts();
	//this->initializeEnemies();
}

Game::~Game()
{
	delete this->windowPointer;
	this->windowPointer = nullptr;		//niet per sé nodig, maar is good practice

	/*delete this->playerObject;
	this->playerObject = nullptr;*/
}

//Accessors
const bool Game::running() const
{
	if (this->windowPointer != NULL)
		return this->windowPointer->isOpen();
}

//Functions
void Game::pollEvents()
{
	//Event polling
	if (this->windowPointer == NULL)
		return;

	while (this->windowPointer->pollEvent(this->myEvent))		//Slaat inputs op, om ze vervolgens te gebruiken (inputs bijv.)
	{
		switch (this->myEvent.type)
		{
		case sf::Event::Closed:
			this->windowPointer->close();
			break;
		case sf::Event::KeyPressed:
			if (this->myEvent.key.code == sf::Keyboard::Escape)
				this->windowPointer->close();
			break;
		}
	}
}


//void Game::updateMousePositions()
//{
	/*
		Update the mouse positions
			- Mouse position relative to window (Vector2i)
	*/

	//this->mousePositionWindow = sf::Mouse::getPosition(*this->windowPointer);	//moet pointer dereferencen om zichzelf een waarde te geven
	//this->mousePositionView = this->windowPointer->mapPixelToCoords(this->mousePositionWindow);
//}

void Game::enemySpawnerUpdate()
{
	//Enemy spawn timer
	if (this->enemySpawnTimer >= this->enemyMaxSpawnTimer)
	{
		int i = 0;
		while (this->enemies[i].hasEnemySpawnedCheck() == true && i < maxEnemies - 1)
		{
			i++;
		}
		if (i < maxEnemies - 1 && this->windowPointer != NULL)
			this->enemies[i].enemySpawn(static_cast<float>(rand()
				% static_cast<int>(this->windowPointer->getSize().x - 1.f)));	//random "X" position CHANGE

		this->enemySpawnTimer = 0.f;
	}
	else
		this->enemySpawnTimer += 1.f;

	if (this->timerSpeedupTimer < this->timerSpeedUpInterval)
	{
		this->timerSpeedupTimer += 1.f * this->deltaTime;
	}
	else
	{
		this->enemyMaxSpawnTimer *= this->spawnRateUpAmount;
		this->timerSpeedupTimer = 0;
	}

}


void Game::updateCollision()
{
	//Check collision between enemies and player
	for (int i = 0; i < maxEnemies - 1; i++)
	{
		/*if (this->player.getPlayerShape().getGlobalBounds()			//ORIGINAL COLLISION
			.intersects(this->enemies[i].getEnemyShape().getGlobalBounds()))
		{
			this->enemies[i].enemyDespawn();	//nu doet dit niks; voor als er later "lives" worden toegevoegt
			lost = true;
		}
		std::cout << this->player.getPlayerShape().getGlobalBounds().top << std::endl;
		std::cout << this->player.getPlayerShape().getGlobalBounds().height << std::endl;*/

		/*if ((this->player.bodyPlayer.currentPosition.x - sizePlayer.x * 0.5f
			- this->enemies[i].enemyBody.currentPosition.x < 10)
			&& (this->player.bodyPlayer.currentPosition.x + sizePlayer.x * 0.5f
				- this->enemies[i].enemyBody.currentPosition.x > -10)
			&& (this->player.bodyPlayer.currentPosition.y - sizePlayer.y * 0.5f
				- this->enemies[i].enemyBody.currentPosition.y < 10)
			&& (this->player.bodyPlayer.currentPosition.y + sizePlayer.y * 0.5f
				- this->enemies[i].enemyBody.currentPosition.y > -10))*/

		//Keeps checking; maybe in a later version these values will change during playtime
		Vector2D sizePlayer = this->player.collisionSizePlayer;
		Vector2D sizeEnemy = this->enemies[i].collisionSizeEnemy;

		/*Player origins: X = Center, Y = top*/
		/*Enemy origins: X = Center, Y = top*/

		//std::cout << this->player.bodyPlayer.currentPosition.y + sizePlayer.y * 0.5f << std::endl;
		//std::cout << this->player.bodyPlayer.currentPosition.y - sizePlayer.y << std::endl;

		if ((this->player.bodyPlayer.currentPosition.x - sizePlayer.x * 0.5f
			< this->enemies[i].bodyEnemy.currentPosition.x + sizeEnemy.x * 0.5f)
			&& (this->player.bodyPlayer.currentPosition.x + sizePlayer.x * 0.5f
				> this->enemies[i].bodyEnemy.currentPosition.x - sizeEnemy.x * 0.5f)
			&& (this->player.bodyPlayer.currentPosition.y
				< this->enemies[i].bodyEnemy.currentPosition.y + sizeEnemy.y)
			&& (this->player.bodyPlayer.currentPosition.y + sizePlayer.y
				> this->enemies[i].bodyEnemy.currentPosition.y - sizeEnemy.y))
		{
			this->enemies[i].enemyDespawn();	//nu doet dit niks; voor als er later "lives" worden toegevoegt
			lost = true;
		}


		/*if (this->enemies[i].getEnemyShape().getPosition().y > this->windowPointer->getSize().y)	//CHANGE!!!
		{
			if (enemies[i].hasEnemySpawnedCheck() == true)
			{
				this->enemies[i].enemyDespawn();
				this->points++;
				//std::cout << points << " " << this->enemies[i].getEnemyShape().getPosition().y << "Enemy Despawned" << std::endl;
			}
		}*/

		if (this->enemies[i].bodyEnemy.currentPosition.y > screenSize.y)
		{
			if (enemies[i].hasEnemySpawnedCheck() == true)
			{
				this->enemies[i].enemyDespawn();
				this->points++;
				//std::cout << points << " " << this->enemies[i].getEnemyShape().getPosition().y << "Enemy Despawned" << std::endl;
			}
		}
	}



}


//Also checks if you win or lose the game
void Game::updateText()
{
	std::stringstream stringStream;

	stringStream << "Points: " << this->points;

	this->uiText.setString(stringStream.str());

	if (this->points >= this->pointsToWin)
		win = true;
}


/*void Game::updateTimeToWin()
{
	this->timePassed += (1 * 0.0167f);
	//std::cout << this->timePassed << std::endl;

	if (timePassed > timeToWin)
		win = true;
}*/

void Game::update()
{
	this->pollEvents();


	if (lost || win)
		return;

	//this->updateTimeToWin();

	this->updateText();

	//this->updateMousePositions();

	this->enemySpawnerUpdate();
	//this->updateEnemies();

	for (int i = 0; i < maxEnemies - 1; i++)
	{
		if (this->enemies[i].hasEnemySpawnedCheck() == true)
		{
			this->enemies[i].update();
		}
	}

	this->player.update();	//paramater is een pointer
	this->updateCollision();
}

/*void Game::renderEnemies()
{
	for (auto& enemyMove : this->enemies)		//"auto&" is snellere for loop methode
	{
		this->windowPointer->draw(enemyMove);
	}
}*/

/*void Game::renderPlayer()
{
	this->windowPointer->draw(playerObject->playerSprite);
}*/

void Game::renderText(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(this->uiText);
}

void Game::render()
{
	/*
		- clear old frame
		- render all objects
		- display frame in window

		Renders the game objects.
	*/
	if (win)
	{
		//SHOW WIN SCREEN
		endScreenSprite.setTexture(this->winScreenTexture);
		windowPointer->draw(this->endScreenSprite);
		this->renderText(*this->windowPointer);
		this->windowPointer->display();
		return;
	}

	if (lost)
	{
		//SHOW LOSE SCREEN
		windowPointer->draw(this->endScreenSprite);
		this->renderText(*this->windowPointer);
		this->windowPointer->display();
		return;
	}

	this->windowPointer->clear(sf::Color(0, 19, 127, 255));

	//Draw game objects
	//this->renderEnemies();

	for (int i = 0; i < maxEnemies - 1; i++)
	{
		this->enemies[i].render(this->windowPointer);
	}


	this->player.render(this->windowPointer);

	this->renderText(*this->windowPointer);		//"dereference" de "windowPointer"

	this->windowPointer->display();
}