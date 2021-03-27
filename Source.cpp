#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<cstdlib>
#include <sstream>

using namespace sf;

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(VideoMode(640, 480), "Party Run");
	window.setFramerateLimit(60);

	//Enemy
	Texture enemyTex;
	Sprite enemy;
	// enemy texture
	if (!enemyTex.loadFromFile("Textures/enemy.png"))
		throw "Could no load enemy.png!";

	enemy.setTexture(enemyTex);

	enemy.setScale(Vector2f(0.8f, 0.8f));
	int enemySpawnTimer = 15;
	std::vector<Sprite> enemys;
	enemys.push_back(Sprite(enemy));

	//player
	Texture playerTex;
	Sprite player;
	int hp = 10;
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Red);
	hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));
	hpBar.setPosition(200.f, 10.f);
	// player texture
	if (!playerTex.loadFromFile("Textures/dummy.png"))
		throw "Could no load dummy.png!";

	player.setTexture(playerTex);
	player.setScale(Vector2f(0.8f, 0.8f));

	// Timer
	int Timer = 0;
	sf::Font arial;
	arial.loadFromFile("Textures/aria.ttf");
	std::ostringstream ssTimer;
	ssTimer << "Time: " << Timer;
	
	sf::Text lblTimer;
	lblTimer.setCharacterSize(30);
	lblTimer.setPosition(10, 10);
	lblTimer.setFont(arial);
	lblTimer.setString(ssTimer.str());

	// score
	int Score = 0;
	sf::Font arias;
	arias.loadFromFile("Textures/arias.ttf");
	std::ostringstream ssScore;
	ssScore << "Score: " << Score;

	sf::Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition(60, 60);
	lblScore.setFont(arias);
	lblScore.setString(ssTimer.str());

	// coin
	//Enemy
	Texture coinTex;
	Sprite coin;
	// enemy texture
	if (!coinTex.loadFromFile("Textures/coin.png"))
		throw "Could no load coin.png!";

	coin.setTexture(coinTex);

	coin.setScale(Vector2f(0.3f, 0.3f));
	int coinSpawnTimer = 15;
	std::vector<Sprite> coins;
	coins.push_back(Sprite(coin));

	

	//GAME LOOP
	while (window.isOpen() && hp > 0)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if(event.type ==Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		//UPDATE
		//PLAYER
		player.setPosition(player.getPosition().x, Mouse::getPosition(window).y);

		if (player.getPosition().y > window.getSize().y - player.getGlobalBounds().height)
			player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);

		if (player.getPosition().y < 0)
			player.setPosition(player.getPosition().x, 0);
		//ENEMY
		for (size_t i = 0; i < enemys.size(); i++)
		{
			enemys[i].move(-7.f, 0.f);

			if (enemys[i].getPosition().x < 0 - enemy.getGlobalBounds().width)
				enemys.erase(enemys.begin() + i);
		}
		//spawn timer
		if (enemySpawnTimer < 40)
			enemySpawnTimer++;
		if (enemySpawnTimer >= 40)
		{
			enemy.setPosition(window.getSize().x, rand()%int(window.getSize().y - enemy.getGlobalBounds().height));
			enemys.push_back(Sprite(enemy));
			enemySpawnTimer = 0;
		}
		// coin
		for (size_t i = 0; i < coins.size(); i++)
		{
			coins[i].move(-5.f, 0.f);

			if (coins[i].getPosition().x < 0 - coin.getGlobalBounds().width)
				coins.erase(coins.begin() + i);
		}
		//spawn coin timer
		if (coinSpawnTimer < 40)
			coinSpawnTimer++;
		if (coinSpawnTimer >= 40)
		{
			coin.setPosition(window.getSize().x, rand() % int(window.getSize().y - coin.getGlobalBounds().height));
			coins.push_back(Sprite(coin));
			coinSpawnTimer = 0;
		}
		// updating score
		Timer++;
		ssTimer.str("");
		ssTimer << "Timer: " << Timer;
		lblTimer.setString(ssTimer.str());
		
		//COLLISION against enemy
		for (size_t i = 0; i < enemys.size(); i++)
		{
			if (player.getGlobalBounds().intersects(enemys[i].getGlobalBounds()))
			{
				hp--;
				enemys.erase(enemys.begin() + i);
			}
		}
		//collision against coin
		for (size_t i = 0; i < coins.size(); i++)
		{
			if (player.getGlobalBounds().intersects(coins[i].getGlobalBounds()))
			{
				Score++;
				ssScore.str("");
				ssScore << "Score: " << Score;
				lblScore.setString(ssScore.str());
				coins.erase(coins.begin() + i);
			}
		}
		//Updating hp bar
		hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));
		//DRAW
		window.clear();

		window.draw(player);

		for (size_t i = 0; i < enemys.size(); i++)
		{
			window.draw(enemys[i]);
		}
		for (size_t i = 0; i < coins.size(); i++)
		{
			window.draw(coins[i]);
		}
		//UI
		window.draw(hpBar);
		window.draw(lblTimer);
		window.draw(lblScore);
		window.display();


	}
}

