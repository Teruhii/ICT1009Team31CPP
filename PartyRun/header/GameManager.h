#pragma once
#include <memory>
#include <string>
#include "stdafx.h"
//#include "Game.h"
#include "../header/StateMachine.h"
#include "../header/AssetManager.h"

//class Game; // Forward declaration of Game class

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	sf::Clock _clock; //clock required to handle framerate and other variable like deltatime

};

//shared pointer will allow us to access GameData from screens that need to utilise the manager intilialised in GameData.
typedef std::shared_ptr<GameData> GameDataRef;

class GameManager {

private:

	//Game* currentGame; (dont need this anymore)

	const float dt = 1.0f / 60.0f;
	//sf::Clock _clock;

	//_data will be used in other Screens to access the datastructure intialized.
	GameDataRef _data = std::make_shared<GameData>();

	void Run();
	
public:

	GameManager(int width, int height, std::string title);
};

