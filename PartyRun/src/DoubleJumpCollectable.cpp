#include "../header/DoubleJumpCollectable.h"




DoubleJumpCollectable::DoubleJumpCollectable(sf::Texture* texture, 
	sf::Vector2f spriteScaling, sf::Vector2f spriteOriginOffset, 
	sf::Vector2f hitBoxSize, sf::Vector2f resetPosition, 
	sf::Vector2f powerUpConstantVelocity, float xLimit, 
	std::string powerUpName)
{

	// Variables
	this->xResetPos = resetPosition.x;
	this->yResetPos = resetPosition.y;
	this->horizontalSpeed = powerUpConstantVelocity.x;
	this->verticalSpeed = powerUpConstantVelocity.y;
	this->xLimit = xLimit;
	this->active = false;
	this->beingUsed = false;

	// Set Body Shape
	this->dJColBodyShape = new sf::RectangleShape();
	this->dJColBodyShape->setSize(hitBoxSize);
	this->dJColBodyShape->setOrigin(hitBoxSize / 2.0f);
	this->dJColBodyShape->setFillColor(sf::Color(0, 255, 0, 255));

	// Create body for platform
	this->dJColBody = new Body(*(this->dJColBodyShape), false, 1000.f, sf::Vector2f(0.f, 0.f), 0.f, false,
		this->verticalSpeed, 0.f, 1.f, this->horizontalSpeed, powerUpName);
	this->dJColBody->setPosition(resetPosition);

	// Set sprite
	this->dJColTexture = *texture;
	this->dJColSprite.setTexture(this->dJColTexture);
	this->dJColSprite.setOrigin(spriteOriginOffset);

	// Scaling image to window
	this->dJColSprite.setScale(spriteScaling);
	this->setActive();
}

DoubleJumpCollectable::~DoubleJumpCollectable()
{
}

bool DoubleJumpCollectable::isActive()
{
	return this->active;
}

void DoubleJumpCollectable::setActive()
{
	this->active = true;
}

bool DoubleJumpCollectable::isBeingUsed()
{
	return this->beingUsed;
}

void DoubleJumpCollectable::setPowerUp()
{
	// Reset position
	this->dJColBody->setPosition(this->xResetPos, this->yResetPos);
	this->active = false;
	std::cout << "Double Jump Collectable has been picked up" << std::endl;
	// Set being used by player
	this->beingUsed = true;
}

void DoubleJumpCollectable::setPosition(sf::Vector2f newPosition)
{
	this->dJColBody->setPosition(newPosition);
}

void DoubleJumpCollectable::movePosition(sf::Vector2f offsetPosition)
{
	this->dJColBody->moveBody(offsetPosition);
}

void DoubleJumpCollectable::activateCollectable(Player* player)
{
	// Reset the player's jump once
	player->resetJump();
	// Set self to not being used
	this->beingUsed = false;
}

void DoubleJumpCollectable::render(sf::RenderTarget& target)
{
	this->dJColSprite.setPosition(this->dJColBody->getPosition());

	target.draw(this->dJColSprite);
	target.draw(*this->dJColBodyShape);
}

void DoubleJumpCollectable::update(float deltaTime)
{
	if (!this->isBeingUsed()) {

		if (this->active) {
			// If reached xlimit, reset position
			if (this->dJColBody->getPosition().x < this->xLimit) {
				// Reset to default
				this->dJColBody->setPosition(this->xResetPos, this->yResetPos);
				this->active = false;
				std::cout << "Double Jump Collectable reset" << std::endl;
			}

			// Move background based on delta time
			this->dJColBody->moveBody(this->horizontalSpeed * deltaTime, 0.f);
			//std::cout << this->platBody->getPosition().x << " Y: " << this->platBody->getPosition().y << std::endl;
		}
	}
}
