#pragma once

#include "../header/stdafx.h"
#include "../header/Screen.h"
#include "../header/EndScreen.h"
#include "../header/Definition.h"
#include "../header/BackgroundManager.h"
#include "../header/BackgroundImage.h"
#include "../header/Player.h"
#include "../header/GameManager.h"
#include "../header/Platform.h"
#include "../header/PlatformManager.h"
#include "../header/Crow.h"
#include "../header/ObstacleManager.h"
#include "../header/hud.h"

class PlayScreen : public Screen {
private:

	GameDataRef _data;
	BackgroundManager* bgManager;
	Player* p1;

	AssetManager* am;
	PlatformManager* platMan;
	ObstacleManager* obstMan;

	Player* p2;
	Player* playerobj;
	hud* shud;




public:
	PlayScreen(GameDataRef data);
	void collisionUpdate(Player* playerobj);
	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};