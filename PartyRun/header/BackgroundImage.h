#pragma once
#include "../header/stdafx.h"

class BackgroundImage
{
public:
	BackgroundImage();
	// spawn x and y pos, reset pos, xlimit, speed, texture
	BackgroundImage(int, int, int, int, int, int, sf::Texture&);
	~BackgroundImage();
	void update(float);
	void render(sf::RenderTarget&);

private:
	// Initial & Reset values
	int xResetPos;
	int yResetPos;

	// Background movement speed
	int speed;
	// Reset x value
	int xLimit;

	// BackgroundTexture
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


};


