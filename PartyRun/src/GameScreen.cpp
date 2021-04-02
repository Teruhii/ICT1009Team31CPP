

/** MOVED TO PLAYSCREEN CLASS

#include "../header/GameScreen.h"
#include "../header/GameManager.h"
#include "../header/BackgroundImage.h"


	//Variable Init implementations
	void Game::initVariables() {
		this->endGame = false;
		this->deltaTime = 0.f;
	}

	void Game::initWindow() {
		this->videoMode = sf::VideoMode(800, 600);
		this->window = new sf::RenderWindow(this->videoMode, "Game window", sf::Style::Close | sf::Style::Titlebar);
		this->window->setFramerateLimit(60);
	}

	// Default constructor for game class
	Game::Game() {
		this->initWindow();
		this->initVariables();
		
		// Testing classes
		this->p1 = new Player();
		this->bgManager = new BackgroundManager();
		//this->gm = gm;
	}

	//constructor & destructor for game class
	Game::Game(GameManager* gm) {
		this->initWindow();
		this->initVariables();
		this->gm = gm;
	}

	Game::~Game() {
		delete this->window;
	}

	//Functions Implementation
	const bool Game::running() const {
		return this->window->isOpen();
	}

	//updating loop for Game class
	void Game::update() {
		// Reset clock
		this->deltaTime = this->gameClock.restart().asSeconds();
		this->pollEvents();



		// Testing update area -----
		this->p1->handleInput();
		this->p1->processInput();

		this->bgManager->update(1.f/60.f);
		// Testing update area end -----
	}

	//render loop for Game class
	void Game::render() {

		//first clear the screen
		this->window->clear();

		//render stuff here

		// Render Testing stuff ---

		
		// Render Testing stuff end ---
		/*sf::Sprite spritetest;
		sf::Texture temptxt;
		bool tempbool = temptxt.loadFromFile("Textures/layer_03.png");
		spritetest.setTexture(temptxt);
		this->window->draw(spritetest);*

		this->bgManager->render(*(this->window));

		this->p1->render(*(this->window));
		//display after rendering stuff
		this->window->display();
	}

	//pollEvent is like event listener
	void Game::pollEvents() {
		while (this->window->pollEvent(this->sfmlEvent)) {
			//checking for event type to decide on what action
			switch (this->sfmlEvent.type) {

			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
				if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
			}
		}
	}

	void Game::changeScoreScreen() {
		/*Game scoreScreen = new ScoreScreen(this->gm)
			this->gm.setGameTo(scoreScreen);*
	}


*/





