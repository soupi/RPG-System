#pragma once

// the map holds the objects on the map and is responsible to handle the collisions between them.

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
	void addGameObject(shared_ptr<GameObject>& obj, const sf::Vector2f& pos);
	void remGameObject(GameObject* obj);
	// handle collisions
	bool canStepOn(GameObject& obj);
	void Step(LocalMap& localmap, GameObject& obj);
	bool Act(LocalMap& localmap, GameObject& obj, sf::FloatRect& box);

	const sf::Vector2f getPosById(int id);

private:
	vector<Tile> _background; // background layer of tilemap - only here an object can be placed
	vector<Tile> _foreground; // foreground layer of tilemap - all tiles here are obsticles
	vector<shared_ptr<GameObject>> _game_objects; // the game objects
	vector<Tile> _top;		  // top layer of tilemap - will be drawn above all

	unsigned _width; // width of the map

// private functions:
	void loadMap(string& filename);
	void loadLayer(std::ifstream&, vector<Tile>& layer);

	// can step on foreground?
	bool canStepOnFG(sf::Vector2f& pos) const;
	bool canStepOnFG(sf::Vector2f& pos, float radius) const;
	bool canStepOnFG(sf::FloatRect& box) const;
};