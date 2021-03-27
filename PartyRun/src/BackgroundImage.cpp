#include "../header/BackgroundImage.h"




BackgroundImage::BackgroundImage()
{
	this->xPos = 0;
	this->yPos = 0;
	this->speed = 0;
	this->xLimit = 0;

	// No background texture
	std::cout << "No Texture selected. Please use parameterised constructor" << std::endl;
}

BackgroundImage::BackgroundImage(int xPos, int yPos,
	int xLimit, int speed, sf::Texture& backgroundTexture)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->speed = speed;
	this->xLimit = xLimit;
	this->backgroundTexture = backgroundTexture;
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->backgroundSprite.setPosition(this->xPos, this->yPos);
	 
	// Testing scaling
	float xScalar = (800.f / 1920.f);
	float yScalar = (600.f / 1080.f);
	this->backgroundSprite.setScale(xScalar, yScalar);
}

BackgroundImage::~BackgroundImage()
{
	// No pointers to delete
}

void BackgroundImage::update(float deltaTime) {

	// If reached xlimit, reset position
	if (this->backgroundSprite.getPosition().x < this->xLimit) {
	// Reset to default
		this->backgroundSprite.setPosition(this->xPos, this->yPos);
	}

	// Move background based on delta time
	this->backgroundSprite.setPosition( 
		this->backgroundSprite.getPosition().x - this->speed * deltaTime, this->backgroundSprite.getPosition().y);
}

void BackgroundImage::render(sf::RenderTarget& target)
{
	target.draw(this->backgroundSprite);
	//std::cout << "Inside BackgroundImage render function" << std::endl;
}

