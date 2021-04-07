#pragma once

#include "../header/stdafx.h"
#include "../header/Body.h"
#include "../header/GameManager.h"
#include "../header/Collectable.h"
#include "../header/Player.h"



class DoubleJumpCollectable : public Collectable
{
public:
	DoubleJumpCollectable(sf::Texture* texture, sf::Vector2f spriteScaling,
		sf::Vector2f spriteOriginOffset, sf::Vector2f hitBoxSize,
		sf::Vector2f resetPosition, sf::Vector2f powerUpConstantVelocity,
		float xLimit, std::string powerUpName);
	~DoubleJumpCollectable();
	// --- Functions ---
	bool isActive();
	void setActive();
	bool isBeingUsed();
	void setPowerUp();
	void setPosition(sf::Vector2f newPosition);
	void movePosition(sf::Vector2f offsetPosition);
	void activateCollectable(Player* player);


	// --- Rendering ---
	void render(sf::RenderTarget& target);

	// --- Physics ---
	void update(float deltaTime);
	Body& getBody() { return *(this->dJColBody); }
private:
	// --- Variables ---
	// Initial & Reset values
	int xResetPos;
	int yResetPos;
	bool active;
	bool beingUsed;

	// Platform movement speed
	float horizontalSpeed;
	float verticalSpeed;

	// Reset x value
	int xLimit;

	// --- Texture ---
	sf::Texture dJColTexture;
	sf::Sprite dJColSprite;

	// --- Physics variables ---
	sf::RectangleShape* dJColBodyShape;
	Body* dJColBody;
};

