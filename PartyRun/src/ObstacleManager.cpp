#include "../header/ObstacleManager.h"





ObstacleManager::ObstacleManager(GameDataRef data) : _data(data)
{
	// Create crows
	for (int i = 0; i < 4; i++) {
		sf::Texture temp;
		temp.loadFromFile("Textures/bird-blue.png");
		fastCrows[i] = new Crow(&temp,
			sf::Vector2f((350.f / 1200.f), (75.f / 256.f)), sf::Vector2f(600, 198),
			sf::Vector2f(350.f, 15.f), sf::Vector2f(1225, 600),
			sf::Vector2f(-20.f, 0.f), -176.f, "crow");
	}
}

ObstacleManager::ObstacleManager(sf::Texture fastCrowTexture, 
	sf::Texture slowCrowTexture, GameDataRef data) : _data(data)
{

	// Variables
	this->fastCrowTimer = this->_data->_clock.getElapsedTime().asSeconds();
	this->slowCrowTimer = this->_data->_clock.getElapsedTime().asSeconds();
	this->fastCrowSpawnTimerRange[0] = 3.f;
	this->fastCrowSpawnTimerRange[1] = 6.f;
	this->slowCrowTimerRange[0] = 8.f;
	this->slowCrowTimerRange[1] = 15.f;
	this->verticalLimitsRange[0] = 50.f;
	this->verticalLimitsRange[1] = 550.f;


	// Create fast crows
	for (int i = 0; i < 10; i++) {
		fastCrows[i] = new Crow(&fastCrowTexture,
			sf::Vector2f((1.f / 1.f), (1.f / 1.f)), sf::Vector2f(0.f, 0.f),
			sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
			sf::Vector2f(-250.f, 0.f), (-175.f), "crow-fast");
		fastCrows[i]->setPosition(sf::Vector2f(1000.f, 0.f));

	}

	// Create slow crows
	for (int i = 0; i < 10; i++) {
		slowCrows[i] = new Crow(&slowCrowTexture,
			sf::Vector2f((1.f / 1.f), (1.f / 1.f)), sf::Vector2f(0.f, 0.f),
			sf::Vector2f(50.f, 50.f), sf::Vector2f(1000.f, 0.f),
			sf::Vector2f(-200.f, 0.f), (-175.f), "crow-slow");
		slowCrows[i]->setPosition(sf::Vector2f(1000.f, 0.f));

	}
}

ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::update(float deltaTime)
{

	// Updating fast crows
	for (int i = 0; i < 10; i++) {
		this->fastCrows[i]->update(deltaTime);

		// Spawn only if
		if (this->_data->_clock.getElapsedTime().asSeconds() -
			this->fastCrowTimer > this->floatRandomInRange(
				this->fastCrowSpawnTimerRange[0], 
				this->fastCrowSpawnTimerRange[1])) {


			// Activate crow if not active
			if (!this->fastCrows[i]->isActive()) {
				// Vertical movement
				this->fastCrows[i]->movePosition(sf::Vector2f(0.f, 
					this->floatRandomInRange(this->verticalLimitsRange[0],
						this->verticalLimitsRange[1])));

				// Activate crow
				this->fastCrows[i]->setActive();
				// Update timer
				this->fastCrowTimer = this->_data->_clock.getElapsedTime().asSeconds();

			}
		}

	}

	// Updating slow crows
	for (int i = 0; i < 10; i++) {
		this->slowCrows[i]->update(deltaTime);

		if (this->_data->_clock.getElapsedTime().asSeconds() -
			this->slowCrowTimer > this->floatRandomInRange(
				this->slowCrowTimerRange[0],
				this->slowCrowTimerRange[1])) {

			// Activate crow if not active
			if (!this->slowCrows[i]->isActive()) {
				// Vertical movement
				std::cout << this->slowCrows[i]->getBody().getPosition().x << " Y B4: " << this->slowCrows[i]->getBody().getPosition().y << std::endl;
				this->slowCrows[i]->movePosition(sf::Vector2f(0.f,
					this->floatRandomInRange(this->verticalLimitsRange[0],
						this->verticalLimitsRange[1])));

				// Activate crow
				this->slowCrows[i] ->setActive();
				std::cout << this->slowCrows[i]->getBody().getPosition().x << " Y Aft: " << this->slowCrows[i]->getBody().getPosition().y << std::endl;

				// Update timer
				this->slowCrowTimer = this->_data->_clock.getElapsedTime().asSeconds();

			}
		}

	}
}

bool ObstacleManager::checkFastCrowCollision(Body& playerBody)
{
	bool returningBool = false;
	for (int i = 0; i < 10; i++) {
		if (returningBool) {

			this->fastCrows[i]->getBody().checkCollision(playerBody, 10000.f);
		}
		else {

			returningBool = this->fastCrows[i]->getBody().checkCollision(playerBody, 10000.f);
		}

	}
	return returningBool;
}

bool ObstacleManager::checkSlowCrowCollision(Body& playerBody)
{
	bool returningBool = false;
	for (int i = 0; i < 10; i++) {
		if (returningBool) {

			this->slowCrows[i]->getBody().checkCollision(playerBody, 10000.f);
		}
		else {

			returningBool = this->slowCrows[i]->getBody().checkCollision(playerBody, 10000.f);
		}

	}
	return returningBool;
}

void ObstacleManager::render(sf::RenderTarget& target)
{

	// Rendering fast crows
	for (int i = 0; i < 10; i++) {
		this->fastCrows[i]->render(target);
	}

	// Rendering slow crows
	for (int i = 0; i < 10; i++) {
		this->slowCrows[i]->render(target);
	}
}

float ObstacleManager::floatRandomInRange(float lowerBound, float upperBound)
{
	return lowerBound + (float)rand() / (RAND_MAX / (upperBound - lowerBound));
}

