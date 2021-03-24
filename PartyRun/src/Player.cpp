#include "../header/Player.h"

	// Constructor
	Player::Player()
	{
		this->state = PlayerState::IDLE;
		// Instantiate FSM with Clips
		this->initTexture();
		this->initSprite();
		this->initAnimations();
		this->initPhysics();
	}

	// Deconstructor
	Player::~Player()
	{
	}

	void Player::render(sf::RenderTarget& target)
	{
		// FSM.playAnimation();
		// OR
		// weapon.playAnimation();
		this->sprite.move(this->velocity); // Update sprite position
		this->updateAnimations();
		target.draw(this->sprite);
	}

	void Player::processInput()
	{
		// Includes physics processing based on inputs
		this->updatePhysics();
	}

	void Player::handleInput()
	{
		// Keyboard input handling to update various info
		this->state = PlayerState::IDLE; // Reset to Idle

		// Process variable changes to update player physics
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			this->move(-1.f, 0.f);
			this->state = PlayerState::RUNNING_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			this->move(1.f, 0.f);
			this->state = PlayerState::RUNNING_RIGHT;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			if (this->state != PlayerState::JUMPING) {
				this->jump(0.f, -1.f);
				this->state = PlayerState::JUMPING;
			}


		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			this->move(0.f, 1.f);
			this->state = PlayerState::FALLING;

		}
		else {
			// Put idle here later
		}
	}

	void Player::updateAnimations()
	{
		
		if (this->state == PlayerState::IDLE) {

			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {// Need to abstract later -----------------------
				this->currentTextureFrame.top = 0;
				this->currentTextureFrame.left = 0;
				 /*for looping of animation only
				// Loop running
				if (this->currentTextureFrame.top >= 64) {
					this->currentTextureFrame.top = 16;
				}*/

				// Reset timer
				this->animationTimer.restart(); // Need to abstract later -----------------------
				this->sprite.setTextureRect(this->currentTextureFrame);
			}
		}
		else if (this->state == PlayerState::RUNNING_LEFT)
		{
			// Timer per animation to abstract later ------------------------------------------------
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
				this->currentTextureFrame.top += 16;
				this->currentTextureFrame.left = 32;

				// Loop running
				if (this->currentTextureFrame.top >= 64) {
					this->currentTextureFrame.top = 16;
				}

				// Reset timer
				this->animationTimer.restart();// Need to abstract later -----------------------
				this->sprite.setTextureRect(this->currentTextureFrame);
			}
		}
		else if (this->state == PlayerState::RUNNING_RIGHT)
		{
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {// Need to abstract later -----------------------
				// Change this
				this->currentTextureFrame.top += 16;
				this->currentTextureFrame.left = 32;

				// Loop jumping animation
				if (this->currentTextureFrame.top >= 64) {
					this->currentTextureFrame.top = 16;
				}

				// Reset timer
				this->animationTimer.restart();// Need to abstract later -----------------------
				this->sprite.setTextureRect(this->currentTextureFrame);
			}
		}
		else
		{
			// For transitioning between states
			// Reset timer
			this->animationTimer.restart();
		}

		

	}

	void Player::move(const float dir_x, const float dir_y)
	{
		// Apply acceleration
		this->velocity.x += dir_x * this->acceleration;
		this->velocity.y += dir_y * this->acceleration;

		// Limit velocity
		if (std::abs(this->velocity.x) > this->maxVelocity) { // Horizontal limiting
			// To keep direction
			// If velocitdadawsdwasy.x is < 0, maxVelocity * -1
			this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
		}

		// Limit velocity
		if (std::abs(this->velocity.y) > this->maxVelocityY) { // Horizontal limiting
			// To keep direction
			// If velocity.x is < 0, maxVelocity * -1
			this->velocity.y = this->maxVelocityY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
		}
	}

	void Player::jump(const float dir_x, const float dir_y)
	{
		// Apply acceleration
		this->velocity.y += dir_y * this->jumpForce;

		/*// Limit velocity
		if (std::abs(this->velocity.y) > this->maxVelocityY) { // Vertical limiting
			// To keep direction
			// If velocity.y is < 0, maxVelocityY * -1
			this->velocity.y = this->maxVelocityY * ((this->velocity.x < 0.f) ? -1.f : 1.f);
		}*/
	}

	void Player::updatePhysics()
	{//remove for now
	 /*
		// Gravity application
		this->velocity.y += 1.0 * this->gravity;
		// For Terminal velocity
		if (std::abs(this->velocity.y) > this->maxVelocityY) {
			this->velocity.y = this->maxVelocityY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
		}*/

		// Decelerate
		this->velocity *= this->drag;

		// Stop excess Deceleration
		if (std::abs(this->velocity.x) < this->minVelocity) { // For left & right
			this->velocity.x = 0;
		}
		if (std::abs(this->velocity.y) < this->minVelocity) { // For up and down
			this->velocity.y = 0;
		}

	}

	void Player::initTexture()
	{
		if (!this->textureSheet.loadFromFile("Textures/entity.png")) {
			std::cout << "Couldn't load the player's sheet. 'entity.png'.";
		}
	}

	void Player::initSprite()
	{
		this->sprite.setTexture(this->textureSheet);
		// Chooses how big the text is rendered and where
		this->currentTextureFrame = sf::IntRect(0, 0, 16, 16);
		this->sprite.setTextureRect(this->currentTextureFrame);
		this->sprite.setScale(2.5f, 2.5f);
	}

	void Player::initAnimations()
	{
		this->animationTimer.restart();
	}

	void Player::initPhysics()
	{
		this->maxVelocity = 10.f;
		this->acceleration = 3.f;
		this->drag = .93f;
		this->minVelocity = 1.f; // threshold to stop moving
		this->gravity = 4.f;
		this->maxVelocityY = 15.f; // Terminal Velocity
		this->jumpForce = 5.f;
	}
