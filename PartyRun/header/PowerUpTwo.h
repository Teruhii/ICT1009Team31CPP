#include "../header/collectable.h"
#include "../header/Body.h"

class PowerUpTwo : public collectable {

private:

	GameDataRef _data;
	float powerUpTimer;
	float powerUpSpawnTimerRange[2];

	// Initial & Reset values
	int xResetPos;
	int yResetPos;
	bool active;

	// PowerUp item movement speed
	float horizontalSpeed;
	float verticalSpeed;

	// --- Texture ---
	sf::Texture powerItemTex;
	sf::Sprite powerItemSprite;

	//Powerup body
	sf::RectangleShape* powerItemShape;


public:

	void initPowerUp();
	void setPowerUp();
	void setPosition(sf::Vector2f newPosition);
	void movePosition(sf::Vector2f offsetPosition);

	void render(sf::RenderTarget& target);
	void update(float deltaTime);
	Body& getBody();


};