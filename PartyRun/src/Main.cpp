#include "../header/stdafx.h"
#include "../header/GameManager.h"
#include "../header/Game.h"

int main()
{


    //Init GameManager object
   GameManager gameManager;

    //Game loop
    while (gameManager.running()) {
        gameManager.update();
        gameManager.render();
    }

    //End application

    return 0;

    /*
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.setFramerateLimit(60);

    // Test player creation
    Player* p1 = new Player();

    while (window.isOpen())
    {
        sf::Event event;

        // ---Polling window events/Update---
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        p1->handleInput();
        p1->processInput();
        // ---update end---



        // ----Render---
        window.clear(sf::Color::Color(255,255,255,255));
        window.draw(shape);
        p1->render(window);

        window.display();   
        // --- Render end ---
    }

    return 0;*/
}