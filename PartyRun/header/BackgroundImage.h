#pragma once
#include "stdafx.h"

class BackgroundImage
{
public:
	BackgroundImage();
	// spawn x and y pos, reset pos, xlimit, baseSpeed, texture, speed multiplier
	BackgroundImage(int, int, int, int, int, int, sf::Texture&, float = 1.f);
	~BackgroundImage();
	void update(float);
	void render(sf::RenderTarget&);
	float getSpeedMultiplier();
	// (new speed multiplier)
	void setSpeedMultiplier(float = 1.f);


private:
	// Initial & Reset values
	int xResetPos;
	int yResetPos;

	// Background movement speed
	int baseSpeed;
	float speedMultiplier;
	// Reset x value
	int xLimit;

	// BackgroundTexture
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


};


