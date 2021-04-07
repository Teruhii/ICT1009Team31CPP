#include "../header/Crow.h"

Crow::Crow()
{

	// Variables
	this->xResetPos = 0.f;
	this->yResetPos = 0.f;
	this->horizontalSpeed = 0.f;
	this->verticalSpeed = 0.f;
	this->xLimit = -10000000.f;
	this->active = false;

	// Set Body Shape
	this->crowBodyShape = new sf::RectangleShape();
	this->crowBodyShape->setSize(sf::Vector2f(10.f, 10.f));
	this->crowBodyShape->setOrigin(sf::Vector2f(10.f, 10.f) / 2.0f);
	this->crowBodyShape->setFillColor(sf::Color(0, 255, 0, 255));

	// Create body for platform
	this->crowBody = new Body(*(this->crowBodyShape), false, 1000.f, sf::Vector2f(0.f, 0.f), 0.f, false,
		this->verticalSpeed, 0.f, 1.f, this->horizontalSpeed, "crow");
	this->crowBody->setPosition(sf::Vector2f(0.f, 0.f));

	// Set sprite
	if (!this->crowTexture.loadFromFile("Textures/bird-odd.png")) {
		std::cout << "Couldn't load the player's sheet. 'bird-odd.png'.";
	}
	this->crowSprite.setTexture(this->crowTexture);
	this->crowSprite.setOrigin(sf::Vector2f(600, 198));

	// Scaling image to window
	float xScalar = (351.5625f / 1200.f);
	float yScalar = (75.f / 256.f);
	this->crowSprite.setScale(xScalar, yScalar);
}

Crow::Crow(sf::Texture* texture, sf::Vector2f spriteScaling, 
	sf::Vector2f spriteOriginOffset, sf::Vector2f hitBoxSize, 
	sf::Vector2f resetPosition, sf::Vector2f crowConstantVelocity, 
	float xLimit, std::string crowName)
{

	// Variables
	this->xResetPos = resetPosition.x;
	this->yResetPos = resetPosition.y;
	this->horizontalSpeed = crowConstantVelocity.x;
	this->verticalSpeed = crowConstantVelocity.y;
	this->xLimit = xLimit;
	this->active = false;

	// Set Body Shape
	this->crowBodyShape = new sf::RectangleShape();
	this->crowBodyShape->setSize(hitBoxSize);
	this->crowBodyShape->setOrigin(hitBoxSize / 2.0f);
	this->crowBodyShape->setFillColor(sf::Color(0, 255, 0, 100));

	// Create body for platform
	this->crowBody = new Body(*(this->crowBodyShape), false, 1000.f, sf::Vector2f(0.f, 0.f), 0.f, false,
		this->verticalSpeed, 0.f, 1.f, this->horizontalSpeed, crowName);
	this->crowBody->setPosition(resetPosition);

	// Set sprite
	this->crowTexture = *texture;
	this->crowSprite.setTexture(this->crowTexture);
	this->crowSprite.setOrigin(spriteOriginOffset);

	// Scaling image to window
	this->crowSprite.setScale(spriteScaling);
	this->setActive();
}

Crow::~Crow()
{
}

bool Crow::isActive()
{
	return this->active;
}

void Crow::setActive()
{
	this->active = true;
}

void Crow::setPosition(sf::Vector2f newPosition)
{
	this->crowBody->setPosition(newPosition);
}

void Crow::movePosition(sf::Vector2f offsetPosition)
{
	this->crowBody->moveBody(offsetPosition);
}

void Crow::render(sf::RenderTarget& target)
{
	this->crowSprite.setPosition(this->crowBody->getPosition());
	target.draw(this->crowSprite);
	target.draw(*this->crowBodyShape);
}

void Crow::update(float deltaTime)
{

	// Update movement
	if (this->active) {
		// If reached xlimit, reset position
		if (this->crowBody->getPosition().x < this->xLimit) {
			// Reset to default
			this->crowBody->setPosition(this->xResetPos, this->yResetPos);
			this->active = false;
			std::cout << "Crow reset" << std::endl;
		}

		// Move background based on delta time
		this->crowBody->moveBody(this->horizontalSpeed * deltaTime, 0.f);
		//std::cout << this->crowBody->getPosition().x << " Y: " << this->crowBody->getPosition().y << std::endl;
	}

}
