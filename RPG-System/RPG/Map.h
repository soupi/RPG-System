#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "Tile.h"
#include "GameObject.h"

using std::list;
using std::vector;
using std::string;

class Controller;

class Map
{
public:
	Map(string filename);
	~Map();
	void handleEvents(const Control& controls);
	void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	void Render(Controller& ctrl);
	void addGameObject(GameObject* obj, unsigned pos);

private:
	vector<Tile> _background;
	vector<Tile> _foreground;
	vector<list<GameObject*>> _game_objects;
	vector<Tile> _top;

	unsigned _width;

	sf::Texture _tileset_back;
	sf::Texture _tileset_fore;
	sf::Texture _tileset_top;

// private functions:
	void loadMap(string& filename);
	void loadLayer(std::ifstream&, vector<Tile>& layer, sf::Texture& tileset);
};