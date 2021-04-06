
#include "../header/stdafx.h"
#include "../header/Body.h"
#include "../header/GameManager.h"

class collectable {

public:

	// --- Functions ---
	virtual bool isActive() = 0;
	virtual void setActive() = 0;
	virtual void setPowerUp() = 0;
	virtual void setPosition(sf::Vector2f newPosition) = 0;
	virtual void movePosition(sf::Vector2f offsetPosition) =0;
	

	// --- Rendering ---
	virtual void render(sf::RenderTarget& target) = 0;

	// --- Physics ---
	virtual void update(float deltaTime) = 0;
	virtual Body& getBody() = 0;

};