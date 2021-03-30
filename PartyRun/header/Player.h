#pragma once
#include "stdafx.h"
#include "Body.h"


	enum class PlayerState {
		IDLE,
		RUNNING_LEFT,
		RUNNING_RIGHT,
		JUMPING,
		FALLING,
		LANDING,
		ATTACK,
		STAGGER,
		DYING
	};


	class Player
	{

	public:
		Player();
		~Player();
		void update(float deltaTime);
		void render(sf::RenderTarget& target);
		void processInput();
		void handleInput();
		void updateAnimations();
		void move(const float dir_x, const float dir_y);
		void jump(const float dir_x, const float dir_y);
		void updatePhysics(float deltatime);
		//static PlayerState playerState; 

	private:
		PlayerState state;
		// FSM
		bool canJump;
		// --- ANIMATION CLIPS ---
		sf::Sprite sprite;
		sf::Texture textureSheet;
		sf::IntRect currentTextureFrame;
		sf::Clock animationTimer;
		void initTexture();
		void initSprite();
		void initAnimations();
		// --- Animation Clips end ---

		// --- Physics Start ---
		sf::Vector2f velocity;
		float acceleration;
		float drag;
		float maxVelocity;
		float minVelocity;
		float gravity;
		float maxVelocityY;
		float jumpForce;
		Body* pBody;
		sf::RectangleShape* pBodyShape;
		void initPhysics();
		// --- Physics End --- 
	};
