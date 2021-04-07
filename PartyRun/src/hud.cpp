#include "../header/hud.h"


hud::hud() {
	this->Timer = 0;
	this->arial.loadFromFile("Textures/aria.ttf");
}

void hud::initHud()
{
	this->distanceScore.setCharacterSize(30);
	this->distanceScore.setPosition((800/2 - 100), (600/2 - 300));
	this->distanceScore.setFont(arial);
	this->distanceScore.setFillColor(sf::Color::Black);
	this->distanceScore.setString(screenTimer.str());

}

void hud::updateHud() {

	this->Timer = Timer++;
	this->screenTimer.str("");
	screenTimer << "Distance: " << Timer;
	this->distanceScore.setString(screenTimer.str());

}

void hud::renderHud(sf::RenderTarget& target)
{
	target.draw(distanceScore);

}
