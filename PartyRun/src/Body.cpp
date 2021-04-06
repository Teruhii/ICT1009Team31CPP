#include "../header/Body.h"


Body::Body()
{
	// Init values
	this->body = new sf::RectangleShape();
	this->isMovable = false;
	this->weight = 1.f;
	this->currentVelocity = new sf::Vector2f(0.f, 0.f);
	this->collider = new Collider(*(this->body));
	this->gravity = 0.f;
	this->isGravity = true;
	this->terminalVelocity = 10.f;
	this->horizontalDecelaration = .93f;
	this->minVelocity = 1.f;
	this->horizontalSpeedLimit = 10.f;
	this->bodyType = "";
}

Body::Body(sf::RectangleShape& bodyShape, bool isMovable, float weight, sf::Vector2f initialVelocity, 
	float gravity, bool isGravity, float terminalVelocity, float horizontalDeceleration, float minVelocity, 
	float horizontalSpeedLimit, std::string bodyType)
{
	// Init values
	this->body = &bodyShape;
	this->isMovable = false;
	if (!(this->isMovable)) {
		this->weight = 1000.f;
	}
	else
	{
		this->weight = weight;
	}
	this->currentVelocity = new sf::Vector2f(initialVelocity.x, initialVelocity.y);
	this->collider = new Collider(*(this->body));
	this->gravity = gravity;
	this->isGravity = isGravity;
	this->terminalVelocity = terminalVelocity;
	this->horizontalDecelaration = horizontalDeceleration;
	this->minVelocity = minVelocity;
	this->horizontalSpeedLimit = horizontalSpeedLimit;
	this->bodyType = bodyType;
}

Body::Body(sf::RectangleShape& bodyShape, bool isMovable, float weight, float initialVelocityX, 
	float initialVelocityY, float gravity, bool isGravity, float terminalVelocity, float horizontalDeceleration, 
	float minVelocity, float horizontalSpeedLimit, std::string bodyType)
{
	// Init values
	this->body = &bodyShape;
	this->isMovable = false;
	if (!(this->isMovable)) {
		this->weight = 1000.f;
	}
	else
	{
		this->weight = weight;
	}
	this->currentVelocity = new sf::Vector2f(initialVelocityX, initialVelocityY);
	this->collider = new Collider(*(this->body));
	this->gravity = gravity;
	this->isGravity = isGravity;
	this->terminalVelocity = terminalVelocity;
	this->horizontalDecelaration = horizontalDeceleration;
	this->minVelocity = minVelocity;
	this->horizontalSpeedLimit = horizontalSpeedLimit;
	this->bodyType = bodyType;
}

Body::~Body()
{
	delete this->currentVelocity;
	delete this->collider;
	delete this->body;
}

std::string Body::getBodyType()
{
	return this->bodyType;
}

// Update the physics of the body
void Body::update(float deltaTime)
{/*
	// Any limits
	// Limit horizontal velocity
	if (std::abs(this->currentVelocity->x) > this->horizontalSpeedLimit) { // Horizontal limiting
		// To keep direction
		// If velocitdadawsdwasy.x is < 0, maxVelocity * -1
		this->currentVelocity->x = this->horizontalSpeedLimit * ((this->currentVelocity->x < 0.f) ? -1.f : 1.f);
	}*/

	// If its affected by gravity
	if (this->isGravity) {

		this->currentVelocity->y += 1.0 * this->gravity;
		// For Terminal velocity
		if (std::abs(this->currentVelocity->y) > this->terminalVelocity) {
			this->currentVelocity->y = this->terminalVelocity * ((this->currentVelocity->y < 0.f) ? -1.f : 1.f);
		}
	}


	// Move the body by its velocity
	this->body->move(this->currentVelocity->x * deltaTime, this->currentVelocity->y * deltaTime);




	// Decelerate
	*(this->currentVelocity) *= this->horizontalDecelaration;

	// Stop excess Deceleration
	if (std::abs(this->currentVelocity->x) < this->minVelocity) { // For left & right
		this->currentVelocity->x = 0;
	}

}

// Add a force onto the body
void Body::addForce(float xForce, float yForce)
{
	this->currentVelocity->x += xForce;
	this->currentVelocity->y += yForce;
}

// Add a force onto the body
void Body::addForce(sf::Vector2f force)
{
	*(this->currentVelocity) += force;
}

void Body::moveBody(float x, float y)
{
	this->body->move(x, y);
}

void Body::moveBody(sf::Vector2f movementVector)
{
	this->body->move(movementVector.x, movementVector.y);
}

void Body::setPosition(float x, float y)
{
	this->body->setPosition(x, y);
}

void Body::setPosition(sf::Vector2f positionVector)
{
	this->body->setPosition(positionVector);
}



sf::Vector2f Body::getCurrentVelocity()
{
	return *(this->currentVelocity);
}

bool Body::checkCollision(Collider other, float push)
{
	return this->collider->CheckCollision(other, push);
}

bool Body::checkCollision(Body& otherBody, float push)
{
	return this->collider->CheckCollision(otherBody.getCollider(), push);
}

Collider Body::getCollider()
{
	return *(this->collider);
}
