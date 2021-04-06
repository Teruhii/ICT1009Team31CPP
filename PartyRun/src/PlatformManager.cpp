#include "../header/PlatformManager.h"




PlatformManager::PlatformManager(GameDataRef data) : _data(data)
{
	// Create ground platforms
	for (int i = 0; i < 4; i++) {
		sf::Texture temp;
		temp.loadFromFile("Textures/bottom-ground.png");
		groundPlatforms[i] = new Platform(&temp,
			sf::Vector2f((350.f / 1200.f), (75.f / 256.f)), sf::Vector2f(600, 198),
			sf::Vector2f(350.f, 15.f), sf::Vector2f(1225, 600),
			sf::Vector2f(-20.f, 0.f), -176.f, "bottom-ground");
	}
}

PlatformManager::PlatformManager(sf::Texture groundTexture, sf::Texture middleTexture, sf::Texture topTexture,
	GameDataRef data) : _data(data) {

	// Variables
	this->middlePlatformTimer = this->_data->_clock.getElapsedTime().asSeconds();
	this->topPlatformTimer = this->_data->_clock.getElapsedTime().asSeconds();
	this->middlePlatformSpawnTimerRange[0] = 3.f;
	this->middlePlatformSpawnTimerRange[1] = 6.f;
	this->topPlatformSpawnTimerRange[0] = 8.f;
	this->topPlatformSpawnTimerRange[1] = 15.f;


	// Create ground platforms
	for (int i = 0; i < 4; i++) {
		groundPlatforms[i] = new Platform(&groundTexture,
			sf::Vector2f((350.f / 1200.f), (75.f / 256.f)), sf::Vector2f(600, 198),
			sf::Vector2f(350.f, 15.f), sf::Vector2f(1225.f, 600.f),
			sf::Vector2f(-200.f, 0.f), (-175.f), "bottom-ground");
		groundPlatforms[i]->setPosition(sf::Vector2f(-175.f + ((i + 1) * (350.f)), 600));
		groundPlatforms[i]->setActive();
	}

	// Create middle platforms
	for (int i = 0; i < 4; i++) {
		middlePlatforms[i] = new Platform(&middleTexture,
			sf::Vector2f((350.f / 1200.f), (75.f / 256.f)), sf::Vector2f(600, 198),
			sf::Vector2f(350.f, 15.f), sf::Vector2f(1225.f, 400.f),
			sf::Vector2f(-200.f, 0.f), (-175.f), "mid-top");
		middlePlatforms[i]->setPosition(sf::Vector2f(1225.f, 400));
		//groundPlatforms[i]->setActive();
	}

	// Create top platforms
	for (int i = 0; i < 4; i++) {
		topPlatforms[i] = new Platform(&topTexture,
			sf::Vector2f((350.f / 1200.f), (75.f / 256.f)), sf::Vector2f(600, 198),
			sf::Vector2f(350.f, 15.f), sf::Vector2f(1225.f, 200.f),
			sf::Vector2f(-200.f, 0.f), (-175.f), "mid-top");
		topPlatforms[i]->setPosition(sf::Vector2f(1225.f, 200));
		//groundPlatforms[i]->setActive();
	}
}

PlatformManager::~PlatformManager()
{

	delete this->groundPlatforms;
	delete this->middlePlatforms;
	delete this->topPlatforms;
}

void PlatformManager::update(float deltaTime)
{

	// Updating ground platforms
	for (int i = 0; i < 4; i++) {
		groundPlatforms[i]->update(deltaTime);

		// If there's an inactive, activate
		if (!groundPlatforms[i]->isActive()) {
			updateOffset(*groundPlatforms[i], *this);
			// Set position of plaform with offset
			groundPlatforms[i]->movePosition(sf::Vector2f(this->groundPlatformOffset, 0.f));
			// Activate platform
			groundPlatforms[i]->setActive();
		}
	}


	// Updating middle platforms
	for (int i = 0; i < 4; i++) {
		middlePlatforms[i]->update(deltaTime);

		if (this->_data->_clock.getElapsedTime().asSeconds() -
			this->middlePlatformTimer > this->middlePlatformSpawnTimerRange[0]
			+ (float)rand() / (RAND_MAX / (this->middlePlatformSpawnTimerRange[1]
				- this->middlePlatformSpawnTimerRange[0]))) {


			// Activate platform if not active
			if (!middlePlatforms[i]->isActive()) {
				this->middlePlatforms[i]->setActive();
				// Update timer
				this->middlePlatformTimer = this->_data->_clock.getElapsedTime().asSeconds();

			}
		}

	}

	// Updating top platforms
	for (int i = 0; i < 4; i++) {
		topPlatforms[i]->update(deltaTime);

		if (this->_data->_clock.getElapsedTime().asSeconds() -
			this->topPlatformTimer > this->topPlatformSpawnTimerRange[0]
			+ (float)rand() / (RAND_MAX / (this->topPlatformSpawnTimerRange[1]
				- this->topPlatformSpawnTimerRange[0]))) {

			// Activate platform if not active
			if (!topPlatforms[i]->isActive()) {
				this->topPlatforms[i]->setActive();

				// Update timer
				this->topPlatformTimer = this->_data->_clock.getElapsedTime().asSeconds();

			}
		}

	}
}

bool PlatformManager::checkGroundCollision(Body& playerBody)
{
	bool returningBool = false;
	for (int i = 0; i < 4; i++) {
		if (returningBool) {

			this->groundPlatforms[i]->getBody().checkCollision(playerBody, 10000.f);
		}
		else {

			returningBool = this->groundPlatforms[i]->getBody().checkCollision(playerBody, 10000.f);
		}

	}
	return returningBool;
}

bool PlatformManager::checkMidTopPlatCollision(Body& playerBody)
{
	bool returningBool = false;
	for (int i = 0; i < 4; i++) {
		if (returningBool) {

			this->middlePlatforms[i]->getBody().checkCollision(playerBody, 10000.f);
		}
		else {

			returningBool = this->middlePlatforms[i]->getBody().checkCollision(playerBody, 10000.f);
		}

	}

	for (int i = 0; i < 4; i++) {
		if (returningBool) {

			this->topPlatforms[i]->getBody().checkCollision(playerBody, 10000.f);
		}
		else {

			returningBool = this->topPlatforms[i]->getBody().checkCollision(playerBody, 10000.f);
		}

	}

	return returningBool;
}

void PlatformManager::render(sf::RenderTarget& target)
{
	// Rendering ground platforms
	for (int i = 0; i < 4; i++) {
		this->groundPlatforms[i]->render(target);
	}

	// Rendering middle platforms
	for (int i = 0; i < 4; i++) {
		this->middlePlatforms[i]->render(target);
	}

	// Rendering top platforms
	for (int i = 0; i < 4; i++) {
		this->topPlatforms[i]->render(target);
	}
}

void PlatformManager::activateNextPlatform(std::string platformType)
{
	if (platformType == "ground-bottom") {

		// Look for unactivated platform
		for (int i = 0; i < 4; i++) {
			if (groundPlatforms[i]->isActive() == false) {
				// Set position of plaform with offset
				groundPlatforms[i]->movePosition(sf::Vector2f(this->groundPlatformOffset, 0.f));
				// Activate platform
				groundPlatforms[i]->setActive();
			}
		}

	}

}

void updateOffset(Platform& plat, PlatformManager& platManager)
{
	std::cout << "Friend was called" << std::endl;
	// Check for which platform
	if (plat.getBody().getBodyType() == "bottom-ground") {
		platManager.groundPlatformOffset = plat.xOffset;
	}
}
