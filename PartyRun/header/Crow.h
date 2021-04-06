#pragma once
#include "stdafx.h"
#include "Body.h"
#include "Animation.h"


class Crow
{
public:
	// --- Constructors ---
	Crow();
	Crow(sf::Texture* texture, sf::Vector2f spriteScaling, 
		sf::Vector2f spriteOriginOffset, sf::Vector2f hitBoxSize, 
		sf::Vector2f resetPosition, sf::Vector2f crowConstantVelocity, 
		float xLimit, std::string crowName);
	~Crow();
	// --- Functions ---
	bool isActive();
	void setActive();
	void setPosition(sf::Vector2f newPosition);
	void movePosition(sf::Vector2f offsetPosition);

	// --- Rendering ---
	void render(sf::RenderTarget& target);

	// --- Physics ---
	void update(float deltaTime);
	Body& getBody() { return *(this->crowBody); }

private:
	// --- Variables ---
	// Initial & Reset values
	int xResetPos;
	int yResetPos;
	bool active;

	// Crow movement speed
	float horizontalSpeed;
	float verticalSpeed;

	// Reset x value
	int xLimit;

	// --- Texture ---
	sf::Texture crowTexture;
	sf::Sprite crowSprite;

	// Body of Crow
	sf::RectangleShape* crowBodyShape;
	Body* crowBody;
};



