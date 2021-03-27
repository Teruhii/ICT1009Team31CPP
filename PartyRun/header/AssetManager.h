#pragma once
#include <map>
#include "stdafx.h"


class AssetManager{
public:
	//constructor & destructor
	AssetManager(){}
	~AssetManager(){}
	
	//Functions
	void LoadTexture (std::string name,std::string filename);
	sf::Texture &GetTexture(std::string name);
	
	void LoadFont (std::string name,std::string filename);
	sf::Font &GetFont (std::string name);
	
private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	
};

