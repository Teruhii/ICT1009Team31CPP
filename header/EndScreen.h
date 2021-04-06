#pragma once 

#include "../header/stdafx.h"
#include "../header/Screen.h"
#include "../header/GameManager.h"

class EndScreen : public Screen {

	GameDataRef _data;
	sf::Texture _backgroundTexture;
	sf::Sprite _background;

public:
	EndScreen(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

};