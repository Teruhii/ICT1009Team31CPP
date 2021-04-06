#pragma once
#include "../header/stdafx.h"
#include "../header/Body.h"


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
		Player();
		~Player();
		void render(sf::RenderTarget& target);

		// --- Interactions ---
		void resetJump();
		bool canFallThrough();
		bool isInvul();
		void setInvul(bool invulStatus);

		// --- Inputs ---
		void processInput();
		void handleInput();

		// --- Animations ---
		void updateAnimations();

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
		bool invul;
		float invulTimer;
		float invulDuration;
		void updateInvultimer(float deltaTime);

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
