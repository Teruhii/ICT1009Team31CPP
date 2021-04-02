#include "../header/MainScreen.h"

MainScreen::MainScreen(GameDataRef data) : _data(data) {}

//initialise this stuff needed to render things into this playscreen
void MainScreen::Init()
{
	this->_data->assets.LoadTexture("mainmenubg", MAINSCREEN_BACKGROUND_FILEPATH);
	//temporarily setting scale here based on the image size
	_background.setScale(800.f/1280.f, 600.f/720.f);
	_background.setTexture(this->_data->assets.GetTexture("mainmenubg"));

}

//this function will handle any key input on this screen.
void MainScreen::HandleInput()
{
	
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		//key press event to go to next screen
		if (sf::Event::KeyPressed == event.type) {
			if (event.key.code == sf::Keyboard::Key::N) {
				//if key N is pressed, proceed to game screen
				this->_data->machine.AddState(StateRef(new PlayScreen(_data)), true);
			}
		}

		//if left mouse button clicked execute event
		if (sf::Event::MouseButtonPressed == event.type) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				this->_data->machine.AddState(StateRef(new PlayScreen(_data)), true);
			}
		}
	}
}

//this function updates the processes inside this screen.
void MainScreen::Update(float dt)
{
	
}

//this will draw whatever that is being put into this screen
void MainScreen::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->_background);
	this->_data->window.display();
}

