#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <ctime>
#include "Vector2D.h"
//#include "UniversalValues.h"


class RigidBody2D
{
private:
	const float gravity = -9.81f;
	const float Mu = 0.02f;		//coefficient of friction	(MOET TUSSEN "0" en "1" zijn); verandert niet dus is "const"
	float mass;
	float Fw;			//weight ownForce = mass times wieght
	float FN;			//ownForce Normal
	//float bounceForce;	//hoeveelheid force die je hebt door tegen de muur te stuiteren
	float mA;			//massa acceleratie
	float fF;			//frictie ownForce		mb illegale namen
	//float netForce;

	Vector2D ownForce;		//kant waar je heen wilt (in Newtons)	wordt meegegeven door "Player"
	Vector2D acceleration;			//acceleratie
	Vector2D currentVelocity;
	Vector2D maxVelocity;

	//UniversalValues universalValues;

	int moveDirectionX;

	const float forceLostOnBounce = 0.15f;


public:
	RigidBody2D();		//parameters zijn om positie mee te geven, values om default position mee te geven

	float const deltaTime = 0.0167f; //framerate = "60", dus "* 0.0167f"

	//"initialzeVariable" wordt 2 keer gedaan; vanuit "constructor" en vanuit "Player.cpp", MOET BETER ALS ER TIJD VOOR IS
	//dit wegens "Warning C26495"
	void initializeVariables(float mass, Vector2D ownForce, Vector2D maxVelocity);		//defaults	sommige variables komen vanuit "Player"
	Vector2D moveDirectionSpeed(Vector2D currentVelocity, int direction = 2);		//default "2"; "2" = niet bewegen
	//float enemyMoveDownSpeed(float currentVelocityY);
	float moveDirectionStopping(Vector2D currentVelocity = Vector2D(0.f, 0.f), int movingDirection = 0, int wallHit = 0);		//default "2"; "2" = niet bewegen
	float bounceAgainstWall(Vector2D currentVelocity, int slipDircetion);

};

