#pragma once
#include "stdafx.h"
#include "Body.h"
#include "Animation.h"


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
		// --- Constructors ---
		Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
		~Player();
		void render(sf::RenderTarget& target);

		// --- Interactions ---
		void resetJump();
		bool canFallThrough();

		// --- Inputs ---
		void processInput();
		void handleInput();

		// --- Animations ---
		void updateAnimations(float deltaTime);

		// --- Physics ---
		void move(const float, const float, float);
		void jump(const float dir_x, const float dir_y);
		void update(float);
		void updatePhysics(float);
		Body& getBody();
		bool checkCollision(Collider, float);
		bool checkCollision(Body& otherBod, float push);
		//static PlayerState playerState; 

	private:
		PlayerState states[2];
		// FSM
		bool canJump;
		bool canFall;
		// --- ANIMATION CLIPS ---
		sf::Sprite sprite;
		sf::Texture textureSheet;
		sf::IntRect currentTextureFrame;
		sf::Clock animationTimer;
		void initTexture();
		void initSprite(sf::Texture* texture);
		void initAnimations();
		sf::RectangleShape body;
		Animation animation;
		unsigned int row;
		float speed;
		bool faceRight;
		// --- Animation Clips end ---

		// --- Physics Start ---
		sf::RectangleShape* pBodyShape;
		Body* pBody;
		sf::Vector2f velocity;
		sf::Vector2f* initialPosition;
		float horizontalMovementSpeed;
		float verticalMovementSpeed;
		float drag;
		float maxVelocity;
		float minVelocity;
		float gravity;
		float maxVelocityY;
		float jumpForce;
		void initPhysics();
		// --- Physics End --- 
	};
