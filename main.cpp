#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
using namespace sf;
using namespace std;

class PlayerClass {
	public:
		bool playerFaceRight;
		float xpos;
		float ypos;
		float xvel;
		float yvel;
		PlayerClass() {
			//initalise player position
			playerFaceRight = true;
			xpos = 0;
			ypos = 0;
			xvel = 0;
			yvel = 0;
		}
		void update(bool playerUp, bool playerDown, bool playerRight, bool playerLeft) {

			if (playerRight) {
				playerFaceRight = true;
				xvel = 3;
			}
			if (playerLeft) {
				playerFaceRight = false;
				xvel = -3;
			}
			if (playerDown) {
				yvel = 3;
			}
			if (playerUp) {
				yvel = -3;
			}
			if (!(playerRight || playerLeft)) {
				xvel = 0;
			}
			if (!(playerUp || playerDown)) {
				yvel = 0;
			}
			xpos += xvel;
			ypos += yvel;
		}

};

int main()
{
	int layer0_x, layer1_x, layer2_x, layer3_x, layer4_x;
	// create the game window
	RenderWindow window(sf::VideoMode(1920, 1080), "PartyRun");
	View View(window.getDefaultView());
	window.setView(View);

	window.setFramerateLimit(60);
	bool playerUp, playerDown, playerLeft, playerRight = false;

	PlayerClass playerObject;

	Texture spriteTexture;
	spriteTexture.loadFromFile("images/player.png");
	Sprite spriteObj(spriteTexture);
	
	Texture backgroundtexture1;
	backgroundtexture1.loadFromFile("images/layer_01.png");
	Texture backgroundtexture2;
	backgroundtexture2.loadFromFile("images/layer_02.png");
	Texture backgroundtexture3;
	backgroundtexture3.loadFromFile("images/layer_03.png");
	Texture backgroundtexture4;
	backgroundtexture4.loadFromFile("images/layer_04.png");
	Texture backgroundtexture5;
	backgroundtexture5.loadFromFile("images/layer_05.png");

	Sprite layer1_0(backgroundtexture1);
	layer1_0.setPosition(0, 0);
	Sprite layer1_1(backgroundtexture1);
	layer1_1.setPosition(0, 0);

	Sprite layer2_0(backgroundtexture2);
	layer2_0.setPosition(0, 0);
	Sprite layer2_1(backgroundtexture2);
	layer2_1.setPosition(0, 0);

	Sprite layer3_0(backgroundtexture3);
	layer3_0.setPosition(0, 0);
	Sprite layer3_1(backgroundtexture3);
	layer3_1.setPosition(0, 0);

	Sprite layer4_0(backgroundtexture4);
	layer4_0.setPosition(0, 0);
	Sprite layer4_1(backgroundtexture4);
	layer4_1.setPosition(0, 0);

	Sprite layer5_0(backgroundtexture5);
	layer5_0.setPosition(0, 0);
	Sprite layer5_1(backgroundtexture5);
	layer5_1.setPosition(0, 0);

	int elapsedTime = 0, offset1 = 0, offset2 = 0, offset3 = 0, offset4 = 0, offset5 = 0;
	float L1 = 0.2, L2 = 0.5, L3 = 2, L4 = 5, L5 = 10; //Individual layer offset speeds to create a parralax effect
	
	while (window.isOpen()) {
		
		Event event;
		while (window.pollEvent(event))
		{ 
			if (event.type == Event::Closed)
				window.close();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Right)) playerRight = true;
		if (Keyboard::isKeyPressed(Keyboard::Left)) playerLeft = true;
		if (Keyboard::isKeyPressed(Keyboard::Up)) playerUp = true;
		if (Keyboard::isKeyPressed(Keyboard::Down)) playerDown = true;
		if (!(Keyboard::isKeyPressed(Keyboard::Right))) playerRight = false;
		if (!(Keyboard::isKeyPressed(Keyboard::Left))) playerLeft = false;
		if (!(Keyboard::isKeyPressed(Keyboard::Up))) playerUp = false;
		if (!(Keyboard::isKeyPressed(Keyboard::Down))) playerDown = false;
		playerObject.update(playerUp, playerDown, playerRight, playerLeft);
		
		window.clear();
        
		offset1--;
		offset2--;
		offset3--;
		offset4--;
		offset5--;
        
		layer1_0.setPosition((offset1*L1), 0);
		layer1_1.setPosition((offset1*L1 + 1920), 0);
		layer2_0.setPosition((offset2*L2), 0);
		layer2_1.setPosition((offset2*L2 + 1920), 0);
		layer3_0.setPosition((offset3*L3), 0);
		layer3_1.setPosition((offset3*L3 + 1920), 0);
		layer4_0.setPosition((offset4*L4), 0);
		layer4_1.setPosition((offset4*L4 + 1920), 0);
		layer5_0.setPosition((offset5)*L5, 0);
		layer5_1.setPosition((offset5*L5 + 1920), 0);

		if (offset1*L1 == -1920) offset1 = 0;
		if (offset2*L2 == -1920) offset2 = 0;
		if (offset3*L3 == -1920) offset3 = 0;
		if (offset4*L4 == -1920) offset4 = 0;
		if (offset5*L5 < -1920) offset5 = 0;

		window.setView(View);
		window.draw(layer1_0);
		window.draw(layer1_1);
		window.draw(layer2_0);
		window.draw(layer2_1);
		window.draw(layer3_0);
		window.draw(layer3_1);
		window.draw(layer4_0);
		window.draw(layer4_1);
		window.draw(layer5_0);
		window.draw(layer5_1);

		window.draw(spriteObj);

		spriteObj.move(Vector2f(playerObject.xvel, playerObject.yvel));
		window.display();
	}
	return 0;
}