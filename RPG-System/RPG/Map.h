#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "Tile.h"

using std::vector;
using std::string;

class Map
{
public:
	Map(string filename);
	~Map();
	//void Update(Hero& hero, float elapsedTime);
	void Update(float elapsedTime);
	void Render(sf::RenderWindow& _window);

private:
	vector<Tile> _background;
	vector<Tile> _foreground;
	//vector<Trigger*> _triggers;
	vector<Tile> _top;

	sf::Texture _tileset_back;
	sf::Texture _tileset_fore;
	sf::Texture _tileset_top;

// private functions:
	void loadMap(string& filename);
	void loadLayer(std::ifstream&, vector<Tile>& layer, sf::Texture& tileset);
};