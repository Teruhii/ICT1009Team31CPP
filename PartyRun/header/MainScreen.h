#pragma once 

#include "../header/stdafx.h"
#include "../header/Screen.h"
#include "../header/GameManager.h"
#include "../header/PlayScreen.h"

class MainScreen : public Screen{

private:
	GameDataRef _data;
	sf::Clock _clock;
	sf::Texture _backgroundTexture;
	sf::Sprite _background;

public:
	MainScreen(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

};