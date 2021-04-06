#pragma once
#include "stdafx.h"
#include "Body.h"
	class PlatformManager;
class Platform
{

public:
	// --- Constructors ---
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	Platform(sf::Texture* texture, sf::Vector2f spriteScaling, sf::Vector2f spriteOriginOffset, sf::Vector2f size, sf::Vector2f resetPosition, sf::Vector2f platformConstantVelocity, float xLimit, std::string platformName);
	~Platform();

	// --- Functions ---
	bool isActive();
	void setActive();
	void setPosition(sf::Vector2f newPosition);
	void movePosition(sf::Vector2f offsetPosition);
	friend void updateOffset(Platform&, PlatformManager&);

	// --- Rendering ---
	void render(sf::RenderTarget& target);

	// --- Physics ---
	void update(float deltaTime);
	Body& getBody() { return *(this->platBody); }

private:
	// --- Variables ---
	// Initial & Reset values
	int xResetPos;
	int yResetPos;
	bool active;

	// Platform movement speed
	float horizontalSpeed;
	float verticalSpeed;

	// Reset x value
	int xLimit;
	float xOffset;

	// --- Texture ---
	sf::Texture platformTexture;
	sf::Sprite platformSprite;

	// --- Physics variables ---
	sf::RectangleShape* platBodyShape;
	Body* platBody;
	std::string bodyType;
};

