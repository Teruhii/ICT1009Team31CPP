#include "../header/GameManager.h"
#include "../header/MainScreen.h"
#include "../header/PlayScreen.h"

/*
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
*/

GameManager::GameManager(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->machine.AddState(StateRef(new MainScreen(this->_data)));
	this->Run();
}

void GameManager::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->_data->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		//using the statemachine to update the change in screen
		this->_data->machine.ProcessStateChanges();

		newTime = this->_data->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);
			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
}