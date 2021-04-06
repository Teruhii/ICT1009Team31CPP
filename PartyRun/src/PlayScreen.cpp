#include "../header/PlayScreen.h"

PlayScreen::PlayScreen(GameDataRef data) : _data(data) {}

void PlayScreen::Init()
{
	//initialise this stuff needed to render things into this playscreen

	this->p1 = new Player();
	this->p2 = new Player();
	this->bgManager = new BackgroundManager();


}

void PlayScreen::HandleInput()
{
	//this function will handle any key input on this screen.


	sf::Event sfmlEvent; //eventlistener for clicks/keypress etc in the game window
	
	while (this->_data->window.pollEvent(sfmlEvent))
	{
		if (sf::Event::Closed == sfmlEvent.type)
		{
			this->_data->window.close();
		}

		if (sf::Event::KeyPressed == sfmlEvent.type) {
			if (sfmlEvent.key.code == sf::Keyboard::Key::N) {
				//if key N is pressed, proceed to game screen

				this->_data->machine.AddState(StateRef(new EndScreen(_data)), true);
			}
		}

		this->p1->handleInput(1);
		this->p2->handleInput(2);
	}

}

void PlayScreen::Update(float dt)
{
	//this function updates the processes inside this screen.
	this->p1->update(dt);
	this->p2->update(dt);
	this->bgManager->update(dt);


}

void PlayScreen::Draw(float dt)
{
	//this will draw whatever that is being put into this screen

	this->_data->window.clear(sf::Color::Red);

	this->bgManager->render(this->_data->window);
	this->p1->render(this->_data->window);
	this->p2->render(this->_data->window);

	this->_data->window.display();
}

