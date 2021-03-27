#pragma once
#include "stdafx.h"

class BackgroundImage
{
public:
	BackgroundImage();
	// spawn x and y pos, xlimit, speed, texture
	BackgroundImage(int, int, int, int, sf::Texture&);
	~BackgroundImage();
	void update(float);
	void render(sf::RenderTarget&);

private:
	// Initial & Reset values
	int xPos;
	int yPos;

	// Background movement speed
	int speed;
	// Reset x value
	int xLimit;

	// BackgroundTexture
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


};


