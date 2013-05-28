#include "Map.h"
#include <iostream>
#include "Utility.h"
#include "Controller.h"
#include <exception>

Map::Map(string filename)
{
	loadMap(filename);
}

Map::~Map() { }

void Map::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	// update game objects
 
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
			(*obj)->Update(ctrl, localmap, elapsedTime);
}

void Map::handleEvents(const Control& controls)
{
	// game objects handle events

	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
		(*obj)->handleEvents(controls);
}

void Map::Render(Controller& ctrl)
{
	// draw background
	for (vector<Tile>::iterator tile = _background.begin(); tile != _background.end(); ++tile)
		tile->draw(ctrl.getWindow());
	// draw foreground
	for (vector<Tile>::iterator tile = _foreground.begin(); tile != _foreground.end(); ++tile)
		tile->draw(ctrl.getWindow());
	// draw game objects
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
		(*obj)->Render(ctrl);


	// draw top
	for (vector<Tile>::iterator tile = _top.begin(); tile != _top.end(); ++tile)
		tile->draw(ctrl.getWindow());
}

void Map::loadMap(string& filename)
{
	std::ifstream mapfile;
	mapfile.open("resources/maps/" + filename);

	if (!mapfile)
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
		
	mapfile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;

	// init
	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		_background.push_back(Tile());
		_foreground.push_back(Tile());
		_top.push_back(Tile());
	}

	loadLayer(mapfile, _background, _tileset_back);
	loadLayer(mapfile, _foreground, _tileset_fore);
	loadLayer(mapfile, _top, _tileset_top);

	mapfile.close();
}

void Map::loadLayer(std::ifstream& mapfile, vector<Tile>& layer, sf::Texture& tileset)
{
	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;

	_width = size_w;

	mapfile.get();

	string tiles;
	getline(mapfile, tiles);

	loadTexture(tileset, "resources/" + tiles);

	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		int tile;
		try {
			mapfile >> tile;
			if (tile)
			{
				layer[i] = Tile(&tileset, tile);
				layer[i].setPos(sf::Vector2f((i%size_w)*float(SCRN_TILE_SIZE), (i/size_w)*float(SCRN_TILE_SIZE)));
			}
		}
		catch (...) { }
	}
}

void Map::addGameObject(shared_ptr<GameObject>& obj, unsigned pos)
{
	if (pos > _background.size())
	{
		std::exception e("bad location for obj on map");
		throw(e);
	}

	obj->setPos(sf::Vector2f((pos%_width)*float(SCRN_TILE_SIZE), (pos/_width)*float(SCRN_TILE_SIZE)));
	_game_objects.push_back(obj);
}

bool Map::canStepOnFG(sf::Vector2f& pos) const
{
	sf::Vector2u my_pos(unsigned(pos.x)/SCRN_TILE_SIZE, unsigned(pos.y)/SCRN_TILE_SIZE);
	if (my_pos.x >= _width || my_pos.y >=  (_foreground.size() / _width)) // out of border
		return false;

	if (_foreground[my_pos.x + my_pos.y*_width].getNum())
		return false;

	return true;
}

bool Map::canStepOnFG(sf::Vector2f& pos, float radius) const
{
	if (canStepOnFG(sf::Vector2f(pos.x - radius, pos.y - radius)) && canStepOnFG(sf::Vector2f(pos.x - radius, pos.y +radius)) &&
		canStepOnFG(sf::Vector2f(pos.x + radius, pos.y - radius)) && canStepOnFG(sf::Vector2f(pos.x + radius, pos.y +radius)))
		return true;
	return false;
}