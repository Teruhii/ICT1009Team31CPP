#pragma once
#include "stdafx.h"
#include "Collider.h"


class Body
{
public:
	Body();
	// (bodyShape, isMovable, weight, initialVelocityX, initialVelocityY, gravity, isGravity, terminalVelocity, deceleration, minVelocity, horizontalSpeedLimit)
	Body(sf::RectangleShape&, bool, float, float, float, float , bool, float, float, float, float);
	// (bodyShape, isMovable, weight, initialVelocity, gravity, isGravity, terminalVelocity, deceleration, minVelocity, horizontalSpeedLimit)
	Body(sf::RectangleShape&, bool, float, sf::Vector2f, float, bool, float, float, float, float);
	~Body();
	// update (float deltaTime)
	void update(float);
	// addForce (float x, float y)
	void addForce(float, float);
	void addForce(sf::Vector2f);
	// Check for collision (Collider, pushForce)
	bool checkCollision(Collider, float);
	// Check for collision (Body, pushForce)
	bool checkCollision(Body, float);
	sf::Vector2f getPosition() { return body->getPosition();}
	Collider getCollider();

private:
	sf::RectangleShape* body;
	Collider* collider;
	sf::Vector2f* currentVelocity;
	float terminalVelocity;
	float gravity;
	// Is movable by other bodies
	bool isMovable;
	// Affected by gravity
	bool isGravity;
	// Used like force
	float weight;
	// Deceleration
	float horizontalDecelaration;
	// horizontalSpeedLimit
	float horizontalSpeedLimit;
	// Min velocity
	float minVelocity;
};
