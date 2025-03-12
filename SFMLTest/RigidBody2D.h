#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <ctime>


class RigidBody2D
{
private:
	const float gravity = -9.81f;
	const float Mu = 0.02f;		//coefficient of friction	(MOET TUSSEN "0" en "1" zijn); verandert niet dus is "const"
	float mass;
	float Fw;			//weight ownForce = mass times wieght
	float FN;			//ownForce Normal
	float ownForce;		//kant waar je heen wilt (in Newtons)	wordt meegegeven door "Player"
	//float bounceForce;	//hoeveelheid force die je hebt door tegen de muur te stuiteren
	float mA;			//massa acceleratie
	float acceleration;			//acceleratie
	float fF;			//frictie ownForce		mb illegale namen
	float netForce;

	float currentVelocity;
	float maxVelocity;

	int moveDirectionX;


public:
	RigidBody2D();		//parameters zijn om positie mee te geven, values om default position mee te geven

	//"initialzeVariable" wordt 2 keer gedaan; vanuit "constructor" en vanuit "Player.cpp", MOET BETER ALS ER TIJD VOOR IS
	//dit wegens "Warning C26495"
	void initializeVariables(float mass, float ownForce, float maxVelocity);		//defaults	sommige variables komen vanuit "Player"
	float moveDirectionSpeed(float currentVelocity = 0.f, int direction = 2);		//default "2"; "2" = niet bewegen
	float moveDirectionStopping(float currentVelocity = 0.f, int movingDirection = 0, int wallHit = 0);		//default "2"; "2" = niet bewegen
	float bounceAgainstWall(float currentVelocity, int slipDircetion);

};

