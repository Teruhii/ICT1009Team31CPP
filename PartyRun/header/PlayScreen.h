#pragma once

#include "../header/stdafx.h"
#include "../header/Screen.h"
#include "../header/EndScreen.h"
#include "../header/Definition.h"
#include "../header/BackgroundManager.h"
#include "../header/BackgroundImage.h"
#include "../header/Player.h"
#include "../header/GameManager.h"

class PlayScreen : public Screen {
private:

	GameDataRef _data;
	BackgroundManager* bgManager;
	Player* p1;
	Player* p2;


public:
	PlayScreen(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};