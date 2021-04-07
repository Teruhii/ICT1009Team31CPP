#pragma once

#include "../header/stdafx.h"
#include "../header/GameManager.h"

class Player;
class Body;

class Collectable {

public:

	// --- Functions ---
	virtual bool isActive() = 0;
	virtual void setActive() = 0;
	virtual bool isBeingUsed() = 0;
	virtual void setPowerUp() = 0;
	virtual void setPosition(sf::Vector2f newPosition) = 0;
	virtual void movePosition(sf::Vector2f offsetPosition) =0;
	virtual void activateCollectable(Player* player) = 0;
	

	// --- Rendering ---
	virtual void render(sf::RenderTarget& target) = 0;

	// --- Physics ---
	virtual void update(float deltaTime) = 0;
	virtual Body& getBody() = 0;

};