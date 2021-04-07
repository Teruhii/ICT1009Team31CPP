#include "../header/Player.h"

// Constructor
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int playerID) :
	animation(texture, imageCount, switchTime)
{
	this->states[0] = PlayerState::IDLE;
	this->states[1] = PlayerState::IDLE;
	this->playerID = playerID;
	this->currentPowerup = NULL;

	// Instantiate FSM with Clips
	this->initTexture();
	this->initSprite(texture);
	this->initAnimations();
	this->initPhysics();
}

// Deconstructor
Player::~Player()
{
}

void Player::update(float deltaTime)
{
	this->processInput();
	this->updatePhysics(deltaTime);
	this->updateInvultimer(deltaTime);
	this->updateAnimations(deltaTime);
	//std::cout << this->pBody->getPosition().x << " Y: " << this->pBody->getPosition().y << std::endl;

}

void Player::render(sf::RenderTarget& target)
{
	// FSM.playAnimation();
	// OR
	// weapon.playAnimation();
	this->sprite.setPosition(this->pBody->getPosition());// move(this->velocity); // Update sprite position

	target.draw(this->sprite);
	//target.draw(*this->pBodyShape);
}

void Player::resetJump()
{
	this->canJump = true;
}

bool Player::canFallThrough()
{
	return this->canFall;
}

bool Player::isInvul()
{
	return this->invul;
}

void Player::setInvul(bool invulStatus)
{
	this->invul = invulStatus;
}

void Player::setPowerup(Collectable* powerUp)
{

	this->currentPowerup = powerUp;

}

bool Player::hasPowerUp()
{
	return (this->currentPowerup != NULL) ? true : false;
}

void Player::processInput()
{
	// Any inputs that need to be processed should be here

}

void Player::handleInput()
{
	// Keyboard input handling to update various info
	this->states[0] = PlayerState::IDLE; // Reset to Idle
	this->states[1] = PlayerState::IDLE; // Reset to Idle
	this->canFall = false;

	switch (this->playerID) {
	case 1:
		// Process variable changes to update player physics
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			this->states[0] = PlayerState::RUNNING_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			this->states[0] = PlayerState::RUNNING_RIGHT;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			if (this->canJump) {
				//this->jump(0.f, -1.f);
				this->pBody->addForce(0.f, -this->jumpForce);
				this->states[1] = PlayerState::JUMPING;
				this->canJump = false;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			//this->move(0.f, 1.f);
			this->canFall = true;
			this->states[1] = PlayerState::FALLING;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
			// Use powerup
			if (this->currentPowerup != NULL) {
				std::cout << "Player has powerup" << std::endl;
				this->usePowerup();
			}
		}
		else {
			// Put idle here later
		}
		break;
	case 2:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			this->states[0] = PlayerState::RUNNING_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			this->states[0] = PlayerState::RUNNING_RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			if (this->canJump) {
				//this->jump(0.f, -1.f);
				this->pBody->addForce(0.f, -this->jumpForce);
				this->states[1] = PlayerState::JUMPING;
				this->canJump = false;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			//this->move(0.f, 1.f);
			this->canFall = true;
			this->states[1] = PlayerState::FALLING;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
			// Use powerup
			if (this->currentPowerup != NULL) {
				std::cout << "Player has powerup" << std::endl;
				this->usePowerup();
			}
		}
		else {
			// Put idle here later
		}
		break;

	}
}

void Player::updateAnimations(float deltaTime)
{

	if (this->states[1] == PlayerState::JUMPING) {

		this->spriteRow = 2;
		if (this->states[0] == PlayerState::RUNNING_LEFT)
		{
			this->facingRight = false;

		}
		else if (this->states[0] == PlayerState::RUNNING_RIGHT)
		{
			this->facingRight = true;
		}
		this->sprite.setTextureRect(this->animation.uvRect);
	}
	else if (this->states[1] == PlayerState::IDLE) {

		this->spriteRow = 0;
		if (this->states[0] == PlayerState::RUNNING_LEFT)
		{
			this->spriteRow = 1;
			this->facingRight = false;

		}
		else if (this->states[0] == PlayerState::RUNNING_RIGHT)
		{
			this->spriteRow = 1;
			this->facingRight = true;
		}
		this->sprite.setTextureRect(this->animation.uvRect);
	}
	else if (this->states[1] == PlayerState::FALLING) {

		this->spriteRow = 7;
		if (this->states[0] == PlayerState::RUNNING_LEFT)
		{
			this->facingRight = false;

		}
		else if (this->states[0] == PlayerState::RUNNING_RIGHT)
		{
			this->facingRight = true;
		}
		this->sprite.setTextureRect(this->animation.uvRect);
	}


	this->animation.Update(this->spriteRow, deltaTime, this->facingRight);


}

void Player::move(const float dir_x, const float dir_y, float deltaTime)
{
	// Apply acceleration
	sf::Vector2f vectorToApply;
	vectorToApply.x = dir_x * this->horizontalMovementSpeed * (deltaTime / 1);
	vectorToApply.y = dir_y * this->verticalMovementSpeed * (deltaTime / 1);

	this->pBody->moveBody(vectorToApply);
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

void Player::updatePhysics(float deltaTime)
{//remove for now
 /*
	// Gravity application
	this->velocity.y += 1.0 * this->gravity;
	// For Terminal velocity
	if (std::abs(this->velocity.y) > this->maxVelocityY) {
		this->velocity.y = this->maxVelocityY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}*/
	/*
	// Decelerate
	this->velocity *= this->drag;

	// Stop excess Deceleration
	if (std::abs(this->velocity.x) < this->minVelocity) { // For left & right
		this->velocity.x = 0;
	}
	if (std::abs(this->velocity.y) < this->minVelocity) { // For up and down
		this->velocity.y = 0;
	}*/

	if (this->states[0] == PlayerState::RUNNING_LEFT) {
		this->move(-1.f, 0.f, deltaTime);
	}
	else if (this->states[0] == PlayerState::RUNNING_RIGHT) {
		this->move(1.f, 0.f, deltaTime);
	}

	this->pBody->update(deltaTime);
	//std::cout << this->pBody->getPosition().x << " Y: " << this->pBody->getPosition().y << std::endl;
}

Body& Player::getBody()
{
	return *(this->pBody);
}

bool Player::checkCollision(Collider col, float push)
{
	return this->pBody->checkCollision(col, push);
}

bool Player::checkCollision(Body& otherBod, float push)
{
	return this->pBody->checkCollision(otherBod, push);
}

void Player::usePowerup()
{
	this->currentPowerup->activateCollectable(this);
	this->currentPowerup = NULL;
}

void Player::updateInvultimer(float deltaTime)
{
	this->invulTimer += deltaTime;
	if (this->invulTimer > this->invulDuration) {
		// Reset invul timer
		this->invulTimer = 0.f;
		this->invul = false;
	}
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/entity.png")) {
		std::cout << "Couldn't load the player's sheet. 'entity.png'.";
	}
}

void Player::initSprite(sf::Texture* texture)
{
	this->sprite.setTexture(*texture);
	this->sprite.setOrigin(30.f,50.f);
	// Chooses how big the text is rendered and where
	//this->currentTextureFrame = sf::IntRect(0, 0, 16, 16);
	//this->sprite.setTextureRect(this->currentTextureFrame);
	//this->sprite.setScale(2.5f, 2.5f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->facingRight = true;
	this->spriteRow = 0;
}

void Player::initPhysics()
{
	// Set player physics variables
	this->maxVelocity = 800.f;
	this->horizontalMovementSpeed = 600.f;
	this->verticalMovementSpeed = 600.f;
	this->drag = .90f;
	this->minVelocity = 1.f; // threshold to stop moving
	this->gravity = 40.f;
	this->maxVelocityY = 8000.f; // Terminal Velocity
	this->jumpForce = 2500.f;
	this->initialPosition = new sf::Vector2f(10.f, 10.f);
	this->canFall = false;
	this->canJump = true;
	this->invulTimer = 0.f;
	this->invulDuration = 3.f;
	this->invul = false;

	// Set player body for physics
	this->pBodyShape = new sf::RectangleShape();
	this->pBodyShape->setSize(sf::Vector2f(60.0f/2.0f, 120.0f/2.0f));
	this->pBodyShape->setOrigin(this->pBodyShape->getSize() / 2.0f);
	this->pBodyShape->setFillColor(sf::Color(255, 0, 0, 100));

	// Create player body for physics
	this->pBody = new Body(*(this->pBodyShape), true, 1.f, sf::Vector2f(0.f, 0.f), this->gravity, true,
		this->maxVelocityY, this->drag, this->minVelocity, this->maxVelocity, "player");
	//this->pBody->setPosition(*initialPosition);
}
