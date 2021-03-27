#pragma once
#include "stdafx.h"

#include "Player.h"
#include "AssetManager.h"
#include "BackgroundImage.h"

class GameManager;

class Game {


private:

	sf::VideoMode videoMode;
	sf::RenderWindow* window; //main render window
	sf::Event sfmlEvent; //eventlistener for clicks/keypress etc in the game window
	bool endGame;

	//initialise the variable&window in constructor only in this class
	void initVariables();
	void initWindow();
	GameManager* gm;
	AssetManager am;

	/// Tempt to delete ----
	Player* p1;
	sf::Texture temptxt;
	BackgroundImage* bgImage1;
	BackgroundImage* bgImage2;
	BackgroundImage* bgImage3;
	BackgroundImage* bgImage4;
	BackgroundImage* bgImage5;
	// Temp to delete end --- 

public:
	//constructor & destructor for game class
	Game();
	Game(GameManager* gm);
	~Game();

	//Accessors(get variables from this class)

	//Modifiers(modify variables from this class)

	//Functions
	const bool running() const;
	void pollEvents();
	void update();
	void render();
	void changeScoreScreen();

};
