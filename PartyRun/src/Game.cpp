#include "../header/Game.h"
#include "../header/GameManager.h"


	//Variable Init implementations
	void Game::initVariables() {
		this->endGame = false;
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
		this->p1 = new Player();
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
		this->pollEvents();
		this->p1->handleInput();
		this->p1->processInput();
	}

	//render loop for Game class
	void Game::render() {

		//first clear the screen
		this->window->clear();

		//render stuff here
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
			this->gm.setGameTo(scoreScreen);*/
	}








