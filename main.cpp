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
	//Create background texture objects from a preset texture file
	//To create the effect of the player and various obstacles moving across the screen, multiple layers are used
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
	
	//Creates 10 layer sprite objects based on the texture objects
	//SetPosition is a function of each sprite object, used to initialize the position of the layers
	//To create a seemless effect for the user, 2 layer objects are used and they move simultaneously across the screen
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
	
	
	int red = 135, green = 205, blue = 235, time = 0, a; //Initialize the sky colour and additional variables
	int offset[5] = {0, 0, 0, 0, 0}; //Initialize layer positions
	//Each layer will use a different offset speed to create a parallax effect
	int L[5] = {1, 2, 5, 7, 14}; //Initialize individual layer offset speeds to create a parallax effect
	Color color(0, 0, 0); //Initialize color object
	
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
        
		//Align the position of the layers to create a 'moving' effect
		layer1_0.setPosition((offset[0]*L[0]), 0);
		layer1_1.setPosition((offset[0]*L[0] + 1920), 0);
		layer2_0.setPosition((offset[1]*L[1]), 0);
		layer2_1.setPosition((offset[1]*L[1] + 1920), 0);
		layer3_0.setPosition((offset[2]*L[2]), 0);
		layer3_1.setPosition((offset[2]*L[2] + 1920), 0);
		layer4_0.setPosition((offset[3]*L[3]), 0);
		layer4_1.setPosition((offset[3]*L[3] + 1920), 0);
		layer5_0.setPosition((offset[4])*L[4], 0);
		layer5_1.setPosition((offset[4]*L[4] + 1920), 0);
		
		//Color object uses 3 values (Red, Green, Blue) to determine the exact color
		//This is adjusted in the game loop
		if (time == 0){ //The time now is day, so we must change the sky to evening orange
			//Slowly fade from sky blue to sunset orange
			if (red < 253) red++; 
			else if (green > 94) green--; 
			else if (blue > 83) blue--;
			else time = 1; //Successfully changed the sky color to evening orange
		}
		else if (time == 1){ //The time now is sunset, so we must change the sky to evening
			if (green > 44) { green--; green--; green--;}
			else if (red > 44) red--; 
			else if (blue < 130) blue++;
			else time = 2; //Successfully changed the sky color to evening blue
		}
		else if (time == 2){ //The time now is evening, so we must change the sky to night
			if (blue > 40) {blue--; blue--; blue--; blue--;}
			else if (red > 4) red--;
			else if (green > 4) green--;
			else time = 3; //Successfully changed the sky color to night blue/black
		}
		else if (time == 3){ //The time now is night, so we must change the sky to morning
			if (red < 253) red++; 
			else if (green > 94) green--; 
			else if (blue > 83) blue--;
			else time = 4; //Successfully changed the sky color to morning
		}
		else if (time == 4){ //The time now is morning, so we change the sky to day
			if (red > 135) {red--; red--; red--;}
			else if (green < 205) green++; 
			else if (blue < 235) {blue++; blue++; blue++; blue++; blue++;}
			else time = 0; //Successfully changed the sky color to day
		}

		//Assign the red, green, blue values in the color object
		color.r = red;
		color.g = green;
		color.b = blue;

		//setColor(color) adjusts the color of each layer according to the time of day
		//Not each layer's colors needs to be adjusted to the time of day
		//Clouds are not included
		layer1_0.setColor(color);
		layer1_1.setColor(color);
		layer3_0.setColor(color);
		layer3_1.setColor(color);
		layer5_0.setColor(color);
		layer5_1.setColor(color);

		a = 0; //Loop through once for every layer
		while (a < 5){
			offset[a]--; 
			if (offset[a]*L[a] < -1920) offset[a] = 0; //End of layer reached, reset the offset to 0 and start again
			a++;
		}

		//Draw each layer and the assets as needed
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
