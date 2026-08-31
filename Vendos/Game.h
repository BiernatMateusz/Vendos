#ifndef GAME
#define GAME

#include <iostream>
#include "StateMenu.h"
#include "StateSpawnPlace.h"
#include <stack>

#include "inputAction.h"
#include <unordered_map>
#include "StateStack.h"

//To add new textures u have to go to: ==== initTextures ==== and add new textures ---- game.cpp


class Game
{

public:
	//Constructors
	Game();
	//Destructor
	virtual ~Game();

	//Update and render functions
	void run();
	void updateSfEvents();
	void update();
	void updateDT();
	void render();
	void endApp();

	//Frame counter
	void frameCounting();

	//Init functions
	void initTextures();
	void initGraphicsData();


	//Graphics functions 
	void LoadNewGraphic(const std::string& name, TextureNames nameOfTxt);

	sf::RenderWindow* getWindow() const;
	GraphicsData* getGraphicsData() const;

protected:


private:
	//FRAME COUNTER FOR TESTS
	sf::Clock clock;
	int frames = 0;
	float timer = 0;
	/////////////////////////


	//variables
	std::unique_ptr<sf::RenderWindow> window;
	int WindowLenght{ 1200 }, WindowHight{ 1000 };
	sf::Event sfEvent;

	sf::Clock dtClock;
	
	std::unordered_map<inputAction, std::unique_ptr<button>>AllKeys;

	//Graphics data structure
	std::unique_ptr<GraphicsData> graphicsData;

	//Time
	float dt;

	//States
	std::unique_ptr<StateMachine> stateMachine;

	//init
	void initializeWindow();
	void initAllKeys();

};

#endif