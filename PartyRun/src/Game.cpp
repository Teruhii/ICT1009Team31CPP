#include "../header/Game.h"
#include "../header/GameManager.h"
#include "../header/BackgroundImage.h"


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
		
		// Testing classes
		this->p1 = new Player();



		sf::Texture temptxt;
		temptxt.loadFromFile("Textures/layer_01.png");
		this->bgImage1 = new BackgroundImage(0, 0, -600, 1, temptxt);

		sf::Texture temptxt1;
		temptxt1.loadFromFile("Textures/layer_02.png");
		this->bgImage2 = new BackgroundImage(0, 0, -600, 2, temptxt1);


		sf::Texture temptxt2;
		temptxt2.loadFromFile("Textures/layer_03.png");
		this->bgImage3 = new BackgroundImage(0, 0, -600, 5, temptxt2);


		sf::Texture temptxt3;
		temptxt3.loadFromFile("Textures/layer_04.png");
		this->bgImage4 = new BackgroundImage(0, 0, -600, 7, temptxt3);


		sf::Texture temptxt4;
		temptxt4.loadFromFile("Textures/layer_05.png");
		this->bgImage5 = new BackgroundImage(0, 0, -600, 14, temptxt4);



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



		// Testing update area -----
		this->p1->handleInput();
		this->p1->processInput();
		this->bgImage1->update(60.f/60.f);
		this->bgImage2->update(60.f/60.f);
		this->bgImage3->update(60.f/60.f);
		this->bgImage4->update(60.f/60.f);
		this->bgImage5->update(60.f/60.f);
		// Testing update area end -----
	}

	//render loop for Game class
	void Game::render() {

		//first clear the screen
		this->window->clear();

		//render stuff here

		// Render Testing stuff ---
		this->bgImage1->render(*(this->window));
		this->bgImage2->render(*(this->window));
		this->bgImage3->render(*(this->window));
		this->bgImage4->render(*(this->window));
		this->bgImage5->render(*(this->window));
		this->p1->render(*(this->window));
		// Render Testing stuff end ---
		/*sf::Sprite spritetest;
		sf::Texture temptxt;
		bool tempbool = temptxt.loadFromFile("Textures/layer_03.png");
		spritetest.setTexture(temptxt);
		this->window->draw(spritetest);*/

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








