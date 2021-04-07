#include "..\header\PowerUpManager.h"

PowerUpManager::PowerUpManager(GameDataRef data) : _data(data)
{
	// Variables
	this->collectableTimer = 0.f;
	this->collectableSpawnTimerRange[0] = 8.f;
	this->collectableSpawnTimerRange[1] = 15.f;
	this->verticalLimitsRange[0] = 50.f;
	this->verticalLimitsRange[1] = 550.f;
	this->numOfDoubleJumps = 0;
	this->numOfInvul = 0;

	// Create collectables
	for (int i = 0; i < 4; i++) {
		sf::Texture temp;
		temp.loadFromFile("Textures/collectable-dj.png");
		collectables[i] = new DoubleJumpCollectable(&temp,
			sf::Vector2f(1.f / 2.f, 1.f / 2.0f), sf::Vector2f(100.f, 120.f),
			sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
			sf::Vector2f(-250.f, 0.f), (-175.f), "collectible-double");
		collectables[i]->setPosition(sf::Vector2f(1000.f, 0.f));
	}
}

// Maximum of 10 collectables in pool
PowerUpManager::PowerUpManager(sf::Texture doubleJumpTexture, 
	sf::Texture invulTexture, GameDataRef data, int minDoubleJumpCount, 
	int minInvulCount) : _data(data)
{

	// Variables
	this->collectableTimer = this->_data->_clock.getElapsedTime().asSeconds();
	this->collectableSpawnTimerRange[0] = 8.f;
	this->collectableSpawnTimerRange[1] = 15.f;
	this->verticalLimitsRange[0] = 50.f;
	this->verticalLimitsRange[1] = 550.f;
	this->numOfDoubleJumps = 0;
	this->numOfInvul = 0;


	// Create random pool of collectables
	for (int i = 0; i < 10; i++) {

		if (this->numOfInvul < minInvulCount) {

			// Spawn invul
			collectables[i] = new DoubleJumpCollectable(&invulTexture,
				sf::Vector2f(1.f / 2.f, 1.f / 2.0f), sf::Vector2f(100.f, 120.f),
				sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
				sf::Vector2f(-250.f, 0.f), (-175.f), "collectible-invul");
			collectables[i]->setPosition(sf::Vector2f(1000.f, 0.f));
		}
		else if (this->numOfDoubleJumps < minDoubleJumpCount) {
			// Spawn double jump
			collectables[i] = new DoubleJumpCollectable(&doubleJumpTexture,
				sf::Vector2f(1.f / 2.f, 1.f / 2.0f), sf::Vector2f(100.f, 120.f),
				sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
				sf::Vector2f(-250.f, 0.f), (-175.f), "collectible-double");
			collectables[i]->setPosition(sf::Vector2f(1000.f, 0.f));
		}
		else {
			// Spawn random between two
			if (this->floatRandomInRange(0, 100) < 50) {
				// Spawn invul
				collectables[i] = new DoubleJumpCollectable(&invulTexture,
					sf::Vector2f(1.f / 2.f, 1.f / 2.0f), sf::Vector2f(100.f, 120.f),
					sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
					sf::Vector2f(-250.f, 0.f), (-175.f), "collectible-invul");
				collectables[i]->setPosition(sf::Vector2f(1000.f, 0.f));
			}
			else
			{
				// Spawn double jump
				collectables[i] = new DoubleJumpCollectable(&doubleJumpTexture,
					sf::Vector2f(1.f / 2.f, 1.f / 2.0f), sf::Vector2f(100.f, 120.f),
					sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
					sf::Vector2f(-250.f, 0.f), (-175.f), "collectible-double");
				collectables[i]->setPosition(sf::Vector2f(1000.f, 0.f));
			}


		}

	}
}

PowerUpManager::~PowerUpManager()
{
}

void PowerUpManager::update(float deltaTime)
{

	// Updating Collectables
	for (int i = 0; i < 10; i++) {
		this->collectables[i] ->update(deltaTime);

		// Spawn only if
		if (this->_data->_clock.getElapsedTime().asSeconds() -
			this->collectableTimer > this->floatRandomInRange(
				this->collectableSpawnTimerRange[0],
				this->collectableSpawnTimerRange[1])) {

			// Only activate if not being used
			if (!this->collectables[i]->isBeingUsed()) {

				// Activate collectable if not active
				if (!this->collectables[i]->isActive()) {
					// Vertical movement
					this->collectables[i]->movePosition(sf::Vector2f(0.f,
						this->floatRandomInRange(this->verticalLimitsRange[0],
							this->verticalLimitsRange[1])));

					// Activate crow
					this->collectables[i]->setActive();
					// Update timer
					this->collectableTimer = this->_data->_clock.getElapsedTime().asSeconds();

				}
			}
		}

	}

}

Collectable* PowerUpManager::checkPowerUpCollision(Body& playerBody)
{
	Collectable* returningCollectable = NULL;
	bool collided = false;
	for (int i = 0; i < 10; i++) {
		if (collided) {

			this->collectables[i]->getBody().checkCollision(playerBody, 0.f);
		}
		else {

			if (this->collectables[i]->getBody().checkCollision(playerBody, 0.f)) {
				collided = true;
				returningCollectable = this->collectables[i];
			}
		}

	}
	return returningCollectable;
}

void PowerUpManager::render(sf::RenderTarget& target)
{
	// Rendering collectables
	for (int i = 0; i < 10; i++) {
		this->collectables[i]->render(target);
	}
}

float PowerUpManager::floatRandomInRange(float lowerBound, float upperBound)
{
	return lowerBound + (float)rand() / (RAND_MAX / (upperBound - lowerBound));
}
