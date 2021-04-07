#include "../header/Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	// Variables
	this->xResetPos = 0.f;
	this->yResetPos = 0.f;
	this->horizontalSpeed = 0.f;
	this->verticalSpeed = 0.f;
	this->xLimit = -10000000.f;
	this->active = false;

	// Set Body Shape
	this->platBodyShape = new sf::RectangleShape();
	this->platBodyShape->setSize(size);
	this->platBodyShape->setOrigin(size / 2.0f);
	this->platBodyShape->setFillColor(sf::Color(0,255,0,255));

	// Create body for platform
	this->platBody = new Body(*(this->platBodyShape), false, 1000.f, sf::Vector2f(0.f, 0.f), 0.f, false,
		this->verticalSpeed, 0.f, 1.f, this->horizontalSpeed, "platform");
	this->platBody->setPosition(position);

	// Set sprite
	this->platformTexture = *texture;
	this->platformSprite.setTexture(this->platformTexture);
	this->platformSprite.setOrigin(sf::Vector2f(600, 198));

	// Scaling image to window
	float xScalar = (351.5625f / 1200.f);
	float yScalar = (75.f / 256.f);
	this->platformSprite.setScale(xScalar, yScalar);

}

Platform::Platform(sf::Texture* texture, sf::Vector2f spriteScaling, 
	sf::Vector2f spriteOriginOffset, sf::Vector2f size, sf::Vector2f 
	resetPosition, sf::Vector2f platformConstantVelocity, float xLimit, 
	std::string platformName) {

	// Variables
	this->xResetPos = resetPosition.x;
	this->yResetPos = resetPosition.y;
	this->horizontalSpeed = platformConstantVelocity.x;
	this->verticalSpeed = platformConstantVelocity.y;
	this->xLimit = xLimit;
	this->active = false;

	// Set Body Shape
	this->platBodyShape = new sf::RectangleShape();
	this->platBodyShape->setSize(size);
	this->platBodyShape->setOrigin(size / 2.0f);
	this->platBodyShape->setFillColor(sf::Color(0, 255, 0, 100));

	// Create body for platform
	this->platBody = new Body(*(this->platBodyShape), false, 1000.f, sf::Vector2f(0.f, 0.f), 0.f, false,
		this->verticalSpeed, 0.f, 1.f, this->horizontalSpeed, platformName);
	this->platBody->setPosition(resetPosition);

	// Set sprite
	this->platformTexture = *texture;
	this->platformSprite.setTexture(this->platformTexture);
	this->platformSprite.setOrigin(spriteOriginOffset);

	// Scaling image to window
	this->platformSprite.setScale(spriteScaling);
	this->setActive();
}


Platform::~Platform()
{
}

bool Platform::isActive()
{
	return this->active;
}

void Platform::setActive()
{
	this->active = true;
}

void Platform::setPosition(sf::Vector2f newPosition)
{
	this->platBody->setPosition(newPosition);
}

void Platform::movePosition(sf::Vector2f offsetPosition)
{
	this->platBody->moveBody(offsetPosition);
}

void Platform::update(float deltaTime) {

	if (this->active) {
		// If reached xlimit, reset position
		if (this->platBody->getPosition().x < this->xLimit) {
			// Reset to default
			this->xOffset = this->platBody->getPosition().x - this->xLimit;
			this->platBody->setPosition(this->xResetPos, this->yResetPos);
			this->active = false;
			std::cout << "Platform reset" << std::endl;
		}

		// Move background based on delta time
		this->platBody->moveBody(this->horizontalSpeed * deltaTime, 0.f);
	//std::cout << this->platBody->getPosition().x << " Y: " << this->platBody->getPosition().y << std::endl;
	}

}


void Platform::render(sf::RenderTarget& target)
{
	this->platformSprite.setPosition(this->platBody->getPosition());

	target.draw(this->platformSprite);
	//target.draw(*this->platBodyShape);
}
