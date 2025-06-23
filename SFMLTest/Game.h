#pragma once

#include "Player.h"
#include "Enemy.h"


class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* windowPointer;
	sf::VideoMode videoMode;
	sf::Event myEvent;


	//Recources
	sf::Font font;
	sf::Texture winScreenTexture;
	sf::Texture loseScreenTexture;

	sf::Sprite endScreenSprite;		//winScreen / loseScreen

	//Text
	sf::Text uiText;

	//Game logic
	unsigned points;
	unsigned const pointsToWin = 30;
	float enemySpawnTimer;
	float enemyMaxSpawnTimer;
	float timerSpeedUpInterval;
	float timerSpeedupTimer;
	const float spawnRateUpAmount = 0.8f;	//bijv. "0.8f"

	const int frameRate = 60;
	const float deltaTime = 0.0167;

	const Vector2D screenSize = Vector2D(1920, 1080);

	int maxEnemies;

	bool win;
	bool lost;

	std::vector<Enemy> enemies;		//Vector Array van Enemy class

	Player player;

	//Private functions
	void initializeVariables();
	void initializeWindow();
	void initializeSprite();
	void initializeFonts();
	void initializeTexts();
	//void initializeEnemies();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void pollEvents();
	void enemySpawnerUpdate();
	void updateCollision();
	void updateText();
	void update();

	void renderText(sf::RenderTarget& renderTarget);
	void render();
};
