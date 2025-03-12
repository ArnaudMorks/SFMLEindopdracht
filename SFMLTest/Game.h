#pragma once

//#include <vector>
#include "Player.h"
#include "Enemy.h"

/*
	Class that acts as the game engine.
	Wrapper class ??
*/


class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* windowPointer;
	sf::VideoMode videoMode;
	sf::Event myEvent;

	//Mouse positions
	//sf::Vector2i mousePositionWindow;	//integer vector2 array
	//sf::Vector2f mousePositionView;		//float vector2 array

	//Recources
	sf::Font font;
	sf::Texture winScreenTexture;
	sf::Texture loseScreenTexture;

	sf::Sprite endScreenSprite;		//winScreen / loseScreen

	//Text
	sf::Text uiText;

	//Game logic
	unsigned points;
	float enemySpawnTimer;
	float enemyMaxSpawnTimer;
	float timerSpeedUpInterval;
	float timerSpeedupTimer;
	float spawnRateUpAmount;	//bijv. "0.8f"

	int maxEnemies;
	bool hittable;			//WERKT NOG NIET
	//bool mouseHeld;
	float timeToWin;
	float timePassed;
	bool win;
	bool lost;

	//Game objects
	//std::vector<sf::RectangleShape> enemies;	//enemy vector array
	//sf::RectangleShape enemy;

	std::vector<Enemy> enemies;		//Vector Array van Enemy class
	//Enemy enemyObject;
	//Player* playerObject;

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
	//void spawnEnemy();

	void pollEvents();
	//void updateMousePositions();
	void enemySpawnerUpdate();
	void updateCollision();
	//void updateEnemies();
	void updateText();
	void updateTimeToWin();
	void update();

	//void renderEnemies();
	//void renderPlayer();
	void renderText(sf::RenderTarget& renderTarget);
	void render();
};
