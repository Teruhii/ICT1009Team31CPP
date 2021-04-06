#pragma once
#include "stdafx.h"
#include "BackgroundImage.h"


class BackgroundManager
{
public:
	BackgroundManager();
	~BackgroundManager();
	void update(float);
	void render(sf::RenderTarget& target);

private:
	

	// Background images needed
	BackgroundImage* bgLayer1[2];
	BackgroundImage* bgLayer2[2];
	BackgroundImage* bgLayer3[2];
	BackgroundImage* bgLayer4[2];
	BackgroundImage* bgLayer5[2];
	void initBackgroundImages();
};
