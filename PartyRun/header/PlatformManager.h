#pragma once
#include "stdafx.h"
#include "Platform.h"
#include "GameManager.h"


class PlatformManager
{
	
public:
	// --- Constructors ---
	PlatformManager(GameDataRef data);
	PlatformManager(sf::Texture groundTexture, sf::Texture middleTexture, sf::Texture topTexture, GameDataRef data);
	~PlatformManager();
	friend void updateOffset(Platform&, PlatformManager&);
	// --- Physics ---
	void update(float deltaTime);
	bool checkGroundCollision(Body& playerBody);
	bool checkMidTopPlatCollision(Body& playerBody);

	// --- Rendering ---
	void render(sf::RenderTarget& target);

private:
	Platform* groundPlatforms[4];
	Platform* middlePlatforms[4];
	Platform* topPlatforms[4];
	GameDataRef _data;

	float groundPlatformOffset;
	float middlePlatformTimer;
	float middlePlatformSpawnTimerRange[2];
	float topPlatformTimer;
	float topPlatformSpawnTimerRange[2];
	void activateNextPlatform(std::string platformType);

};
