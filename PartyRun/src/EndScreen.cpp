#include "../header/EndScreen.h"
#include "../header/Definition.h"


EndScreen::EndScreen(GameDataRef data) : _data(data) {}

//initialise this stuff needed to render things into this playscreen
void EndScreen::Init()
{
	this->_data->assets.LoadTexture("endscreenbg", ENDSCREEN_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.GetTexture("endscreenbg"));
	_background.setScale(800.f / 1920.f, 600.f / 1080.f);

}

//this function will handle any key input on this screen.
void EndScreen::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (sf::Event::KeyPressed == event.type) {
			if (event.key.code == sf::Keyboard::Key::Escape) {

				this->_data->window.close();
			}
		}

	}
}
//this function updates the processes inside this screen.
void EndScreen::Update(float dt)
{
	
}

//this will draw whatever that is being put into this screen
void EndScreen::Draw(float dt)
{
	
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->_background);
	this->_data->window.display();
}

