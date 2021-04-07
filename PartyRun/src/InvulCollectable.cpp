#include "../header/InvulCollectable.h"




InvulCollectable::InvulCollectable(sf::Texture* texture,
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
	this->invulBodyShape = new sf::RectangleShape();
	this->invulBodyShape->setSize(hitBoxSize);
	this->invulBodyShape->setOrigin(hitBoxSize / 2.0f);
	this->invulBodyShape->setFillColor(sf::Color(0, 255, 0, 255));

	// Create body for platform
	this->invulBody = new Body(*(this->invulBodyShape), false, 1000.f, sf::Vector2f(0.f, 0.f), 0.f, false,
		this->verticalSpeed, 0.f, 1.f, this->horizontalSpeed, powerUpName);
	this->invulBody->setPosition(resetPosition);

	// Set sprite
	this->invulTexture = *texture;
	this->invulSprite.setTexture(this->invulTexture);
	this->invulSprite.setOrigin(spriteOriginOffset);

	// Scaling image to window
	this->invulSprite.setScale(spriteScaling);
	this->setActive();
}

InvulCollectable::~InvulCollectable()
{
}

bool InvulCollectable::isActive()
{
	return this->active;
}

void InvulCollectable::setActive()
{
	this->active = true;
}

bool InvulCollectable::isBeingUsed()
{
	return this->beingUsed;
}

void InvulCollectable::setPowerUp()
{
	// Reset position
	this->invulBody->setPosition(this->xResetPos, this->yResetPos);
	this->active = false;
	std::cout << "Invul Collectable has been picked up" << std::endl;
	// Set being used by player
	this->beingUsed = true;
}

void InvulCollectable::setPosition(sf::Vector2f newPosition)
{
	this->invulBody->setPosition(newPosition);
}

void InvulCollectable::movePosition(sf::Vector2f offsetPosition)
{
	this->invulBody->moveBody(offsetPosition);
}

void InvulCollectable::activateCollectable(Player* player)
{
	// Reset the player's jump once
	player->setInvul(true);
	// Set self to not being used
	this->beingUsed = false;
}

void InvulCollectable::render(sf::RenderTarget& target)
{
	this->invulSprite.setPosition(this->invulBody->getPosition());

	target.draw(this->invulSprite);
	target.draw(*this->invulBodyShape);
}

void InvulCollectable::update(float deltaTime)
{
	if (!this->isBeingUsed()) {

		if (this->active) {
			// If reached xlimit, reset position
			if (this->invulBody->getPosition().x < this->xLimit) {
				// Reset to default
				this->invulBody->setPosition(this->xResetPos, this->yResetPos);
				this->active = false;
				std::cout << "Invul Collectable reset" << std::endl;
			}

			// Move background based on delta time
			this->invulBody->moveBody(this->horizontalSpeed * deltaTime, 0.f);
			//std::cout << this->platBody->getPosition().x << " Y: " << this->platBody->getPosition().y << std::endl;
		}
	}
}
