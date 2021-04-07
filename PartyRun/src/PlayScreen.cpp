#include "../header/PlayScreen.h"

PlayScreen::PlayScreen(GameDataRef data) : _data(data) {}

void PlayScreen::Init()
{
	//initialise this stuff needed to render things into this playscreen
	this->shud = new hud();
	this->am = new AssetManager();
	this->bgManager = new BackgroundManager();
	this->shud->initHud();


	this->am->LoadTexture("player1", "Textures/player-penguin.png");
	this->am->LoadTexture("player2", "Textures/player-fox.png");
	//this->am->LoadTexture("bottom-ground", "Textures/bottom-ground.png");
	
	this->am->LoadTexture("bottom-ground", "Textures/bottom-ground.png");
	this->am->LoadTexture("mid-top-plank", "Textures/mid-top-plank.png");
	this->platMan = new PlatformManager(this->am->GetTexture("bottom-ground"),
		this->am->GetTexture("mid-top-plank"), this->am->GetTexture("mid-top-plank"), this->_data);
	/*
	this->plat1 = new Platform(&this->am->GetTexture("plank"), 
		sf::Vector2f((351.5625f / 1200.f), (75.f / 256.f)), sf::Vector2f(600, 198),
		sf::Vector2f(351.5625f, 15.f), sf::Vector2f(975, 600),
		sf::Vector2f(-20.f, 0.f), -176.f, "bottom-ground");*/

	this->p1 = new Player(&(this->am->GetTexture("player1")), sf::Vector2u(3, 9), 0.3f, 1);
	this->p2 = new Player(&(this->am->GetTexture("player2")), sf::Vector2u(3, 9), 0.3f, 2);

	this->am->LoadTexture("crow-slow", "Textures/bird-blue.png");
	this->am->LoadTexture("crow-fast", "Textures/bird-yellow.png");
	this->obstMan = new ObstacleManager(this->am->GetTexture("crow-fast"),
		this->am->GetTexture("crow-slow"), this->_data);

	


}

void PlayScreen::HandleInput()
{
	//this function will handle any key input on this screen.


	sf::Event sfmlEvent; //eventlistener for clicks/keypress etc in the game window
	
	while (this->_data->window.pollEvent(sfmlEvent))
	{
		if (sf::Event::Closed == sfmlEvent.type)
		{
			this->_data->window.close();
		}

		if (sf::Event::KeyPressed == sfmlEvent.type) {
			if (sfmlEvent.key.code == sf::Keyboard::Key::N) {
				//if key N is pressed, proceed to game screen

				this->_data->machine.AddState(StateRef(new EndScreen(_data)), true);
			}
		}

		this->p1->handleInput();
		this->p2->handleInput();
	}

}

void PlayScreen::Update(float dt)
{
	//this function updates the processes inside this screen.
	this->p1->update(dt);
	this->p2->update(dt);
	this->bgManager->update(dt);
	this->platMan->update(dt);
	this->obstMan->update(dt);
	this->shud->updateHud();

	// --- Collision updates ---
	collisionUpdate(p1);
	collisionUpdate(p2);

	//this->plat1->update(dt);
	/*if (this->p1->checkCollision((this->plat1->getBody()), 0.f)) {
		std::cout << this->p1->getBody().getBodyType() << " is in colission with " << \
			this->plat1->getBody().getBodyType() << std::endl;
		this->p1->resetJump();
	}
	else {
		//std::cout << "No collision" << std::endl;
	}*/
}

void PlayScreen::Draw(float dt)
{
	//this will draw whatever that is being put into this screen

	this->_data->window.clear(sf::Color::Red);

	this->bgManager->render(this->_data->window);
	this->platMan->render(this->_data->window);
	this->obstMan->render(this->_data->window);
	this->p1->render(this->_data->window);
	this->p2->render(this->_data->window);
	this->shud->renderHud(this->_data->window);


	this->_data->window.display();
}


void PlayScreen::collisionUpdate(Player* playerobj) {

	this->playerobj = playerobj;

	if (this->platMan->checkGroundCollision(this->playerobj->getBody())) {
		this->playerobj->resetJump();
	}

	if (!this->playerobj->canFallThrough()) {
		if (this->platMan->checkMidTopPlatCollision(this->playerobj->getBody())) {
			this->playerobj->resetJump();
		}
	}

	if (!this->playerobj->isInvul()) {
		if (this->obstMan->checkFastCrowCollision(this->playerobj->getBody())) {
			// Player hit by fast crow
			std::cout << "Player hit by fast crow" << std::endl;
			this->playerobj->setInvul(true);
			this->playerobj->move(-.1f, -.1f, 1.f);
		}

		if (this->obstMan->checkSlowCrowCollision(this->playerobj->getBody())) {
			// Player hit by slow crow
			std::cout << "Player hit by slow crow" << std::endl;
			this->playerobj->setInvul(true);

			this->playerobj->move(-.1f, -.1f, 1.f);
		}
	}
}

/*
* original code for collision update
if (this->platMan->checkGroundCollision(this->p1->getBody())) {
		this->p1->resetJump();
		this->p2->resetJump();
	}

	if (!this->p1->canFallThrough()) {
		if (this->platMan->checkMidTopPlatCollision(this->p1->getBody())) {
			this->p1->resetJump();
		}
	}

	if (!this->p1->isInvul()) {
		if (this->obstMan->checkFastCrowCollision(this->p1->getBody())) {
			// Player hit by fast crow
			std::cout << "Player hit by fast crow" << std::endl;
			this->p1->setInvul(true);
			this->p1->move(-.1f, -.1f, 1.f);
		}

		if (this->obstMan->checkSlowCrowCollision(this->p1->getBody())) {
			// Player hit by slow crow
			std::cout << "Player hit by slow crow" << std::endl;
			this->p1->setInvul(true);

			this->p1->move(-.1f, -.1f, 1.f);
		}
	}
*/