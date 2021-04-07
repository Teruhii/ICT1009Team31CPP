#include "../header/stdafx.h"
#include <iostream>
#include <sstream>

class hud {

	// Timer
	int Timer;
	sf::Font arial;
	sf::Text distanceScore;
	std::ostringstream screenTimer;

public:
	hud();
	~hud();

	void initHud();
	void renderHud(sf::RenderTarget& target);
	void updateHud();
	

	
	

};