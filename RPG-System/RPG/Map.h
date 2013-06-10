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
using std::shared_ptr;
class Controller;

class Map
{
public:
	Map(string filename);
	~Map();
	void handleEvents(const Control& controls);
	void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	void Render(Controller& ctrl);
	void addGameObject(shared_ptr<GameObject>& obj, unsigned pos);
	void addGameObject(shared_ptr<GameObject>& obj, sf::Vector2f& pos);
	void remGameObject(GameObject* obj);
	bool canStepOn(GameObject& obj);
	void Step(LocalMap& localmap, GameObject& obj);
	void Act(LocalMap& localmap, GameObject& obj, sf::FloatRect& box);

	const sf::Vector2f getPosById(int id);

private:
	vector<Tile> _background;
	vector<Tile> _foreground;
	vector<shared_ptr<GameObject>> _game_objects;
	vector<Tile> _top;

	unsigned _width;

	sf::Texture _tileset_back;
	sf::Texture _tileset_fore;
	sf::Texture _tileset_top;

// private functions:
	void loadMap(string& filename);
	void loadLayer(std::ifstream&, vector<Tile>& layer, sf::Texture& tileset);

	bool canStepOnFG(sf::Vector2f& pos) const;
	bool canStepOnFG(sf::Vector2f& pos, float radius) const;
	bool canStepOnFG(sf::FloatRect& box) const;
};