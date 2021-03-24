#include "../header/GameManager.h"
#include "../header/Game.h"


	GameManager::GameManager()
	{
		this->currentGame = new Game();
	}

	void GameManager::update()
	{
		this->currentGame->update();
	}

	void GameManager::render()
	{
		this->currentGame->render();
		
	}

	void GameManager::setGameTo(Game* game)
	{
		//delete this->currentGame;
		this->currentGame = game;
	}

	const bool GameManager::running() const
	{
		return this->currentGame->running();
	}





