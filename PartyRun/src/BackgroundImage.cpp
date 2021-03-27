#include "../header/BackgroundImage.h"




BackgroundImage::BackgroundImage()
{
	this->xResetPos = 0;
	this->yResetPos = 0;
	this->speed = 0;
	this->xLimit = 0;

	// No background texture
	std::cout << "No Texture selected. Please use parameterised constructor" << std::endl;
}

BackgroundImage::BackgroundImage(int xSpawnPos, int ySpawnPos, int xResetPos, int yResetPos,
	int xLimit, int speed, sf::Texture& backgroundTexture)
{
	this->xResetPos = xResetPos;
	this->yResetPos = yResetPos;
	this->speed = speed;
	this->xLimit = xLimit;
	this->backgroundTexture = backgroundTexture;
	this->backgroundSprite.setTexture(this->backgroundTexture);

	 
	// Scaling image to window
	float xScalar = (800.f / 1920.f);
	float yScalar = (600.f / 1080.f);
	this->backgroundSprite.setScale(xScalar, yScalar);

	// Set pos after scaling
	this->backgroundSprite.setPosition(xSpawnPos, ySpawnPos);
}

BackgroundImage::~BackgroundImage()
{
	// No pointers to delete
}

void BackgroundImage::update(float deltaTime) {

	// If reached xlimit, reset position
	if (this->backgroundSprite.getPosition().x < this->xLimit) {
	// Reset to default
		float overFlow =  this->backgroundSprite.getPosition().x - this->xLimit;
		this->backgroundSprite.setPosition(this->xResetPos + overFlow, this->yResetPos);
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

