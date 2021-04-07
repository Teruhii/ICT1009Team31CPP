#pragma once
#pragma once
#include "../header/stdafx.h"
#include "../header/DoubleJumpCollectable.h"
#include "../header/GameManager.h"


class PowerUpManager
{
public:
	PowerUpManager(GameDataRef data);
	PowerUpManager(sf::Texture doubleJumpTexture, 
		sf::Texture invulTexture, GameDataRef data,
		int minDoubleJumpCount = 0, int minInvulCount = 0);

	~PowerUpManager();


	// --- Physics ---
	void update(float deltaTime);
	Collectable* checkPowerUpCollision(Body& playerBody);

	// --- Rendering ---
	void render(sf::RenderTarget& target);

private:
	Collectable* collectables[10];
	GameDataRef _data;

	float collectableTimer;
	float collectableSpawnTimerRange[2];
	float verticalLimitsRange[2];
	int numOfDoubleJumps;
	int numOfInvul;

	// --- Helper function ---
	float floatRandomInRange(float lowerBound, float upperBound);
};
