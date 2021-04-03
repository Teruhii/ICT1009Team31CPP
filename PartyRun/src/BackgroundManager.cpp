#include "../header/BackgroundManager.h"



BackgroundManager::BackgroundManager()
{
	this->initBackgroundImages();
}

BackgroundManager::~BackgroundManager()
{

}

void BackgroundManager::update(float deltaTime)
{

	// Update each layer
	for (int i = 0; i < 2; i++) {
		this->bgLayer1[i]->update(deltaTime);
		this->bgLayer2[i]->update(deltaTime);
		this->bgLayer3[i]->update(deltaTime);
		this->bgLayer4[i]->update(deltaTime);
		this->bgLayer5[i]->update(deltaTime);
	}

}

void BackgroundManager::render(sf::RenderTarget& target)
{
	// Render each layer
	for (int i = 0; i < 2; i++) {
		this->bgLayer1[i]->render(target);
	}

	for (int i = 0; i < 2; i++) {
		this->bgLayer2[i]->render(target);
	}
	for (int i = 0; i < 2; i++) {
		this->bgLayer3[i]->render(target);
	}

	for (int i = 0; i < 2; i++) {
		this->bgLayer4[i]->render(target);
	}
	for (int i = 0; i < 2; i++) {
		this->bgLayer5[i]->render(target);
	}

}


void BackgroundManager::initBackgroundImages()
{

	// Create backgrounds for each layer
	for (int i = 0; i < 2; i++) {
		sf::Texture temptxt;
		temptxt.loadFromFile(PLAYBG_LAY1);
		this->bgLayer1[i] = new BackgroundImage(0 + 800 * i, 0, 800, 0, -800, 60, temptxt);
	}

	for (int i = 0; i < 2; i++) {
		sf::Texture temptxt;
		temptxt.loadFromFile(PLAYBG_LAY2);
		this->bgLayer2[i] = new BackgroundImage(0 + 800 * i, 0, 800, 0, -800, 120, temptxt);
	}

	for (int i = 0; i < 2; i++) {
		sf::Texture temptxt;
		temptxt.loadFromFile(PLAYBG_LAY3);
		this->bgLayer3[i] = new BackgroundImage(0 + 800 * i, 0, 800, 0, -800, 300, temptxt);
	}

	for (int i = 0; i < 2; i++) {
		sf::Texture temptxt;
		temptxt.loadFromFile(PLAYBG_LAY4);
		this->bgLayer4[i] = new BackgroundImage(0 + 800 * i, 0, 800, 0, -800, 420, temptxt);
	}

	for (int i = 0; i < 2; i++) {
		sf::Texture temptxt;
		temptxt.loadFromFile(PLAYBG_LAY5);
		this->bgLayer5[i] = new BackgroundImage(0 + 800 * i, 0, 800, 0, -800, 840, temptxt);
	}

}