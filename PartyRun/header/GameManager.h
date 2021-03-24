#pragma once
#include "stdafx.h"
#include "Game.h"

	class Game; // Forward declaration of Game class

class GameManager {

private:

	Game* currentGame;


public:

	GameManager();
	void update();
	void render();
	void setGameTo(Game* game);
	const bool running() const;
};


