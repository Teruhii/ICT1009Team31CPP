#include "../header/GameManager.h"
#include "../header/MainScreen.h"
#include "../header/PlayScreen.h"

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
		// the actual frame time of ur machine
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		// Accumulator tracks the time over the while loops
		// accumulator is what u check for since the last frame update
		// Every time the accumulator is 1/60 which is 60fps. means that 1 frame passed.
		// THEN u decide to update the game ONCE
		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);

			// Minus dt to reset the accumulator to 0. BUT since u always have chance of overflow, need to cater for that
			// Hence u do not use = 0 but use -= dt.
			accumulator -= dt;
			// accumulator = 0.5/60
		}

		// Fraction of the next frame that has passed
		// e.g 0.5 / 1
		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
}