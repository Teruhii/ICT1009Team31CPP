#pragma once
#include <SFML\Graphics.hpp>

class PauseMenu;
class Player;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	Player* player;
	sf::Texture texture;

	TileMap* tileMap;

	//Functions
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//functions
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void update PauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);

}


}



