#pragma once
#include "stdafx.h"
#include "Crow.h"
#include "GameManager.h"


class ObstacleManager
{
public:
	ObstacleManager(GameDataRef data);
	ObstacleManager(sf::Texture fastCrowTexture, sf::Texture slowCrowTexture, GameDataRef data);

	~ObstacleManager();


	// --- Physics ---
	void update(float deltaTime);
	bool checkFastCrowCollision(Body& playerBody);
	bool checkSlowCrowCollision(Body& playerBody);

	// --- Rendering ---
	void render(sf::RenderTarget& target);

private:
	Crow* fastCrows[10];
	Crow* slowCrows[10];
	GameDataRef _data;

	float fastCrowTimer;
	float fastCrowSpawnTimerRange[2];
	float slowCrowTimer;
	float slowCrowTimerRange[2];
	float verticalLimitsRange[2];
	float horizontalResetXPos;

	// --- Helper function ---
	float floatRandomInRange(float lowerBound, float upperBound);
};
