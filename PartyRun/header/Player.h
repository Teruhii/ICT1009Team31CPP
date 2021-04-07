#pragma once
#include "../header/stdafx.h"
#include "../header/Body.h"
#include "../header/Animation.h"


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
		Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int playerID);
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
		void updateAnimations(float deltaTime);

		// --- Physics ---
		void move(const float, const float, float);
		void jump(const float dir_x, const float dir_y);
		void update(float deltaTime);
		void updatePhysics(float deltaTime);
		Body& getBody();
		bool checkCollision(Collider, float);
		bool checkCollision(Body& otherBod, float push);
		//static PlayerState playerState; 

	private:
		PlayerState states[2];
		int playerID;

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
		Animation animation;
		int spriteRow;
		bool facingRight;
		void initTexture();
		void initSprite(sf::Texture* texture);
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
