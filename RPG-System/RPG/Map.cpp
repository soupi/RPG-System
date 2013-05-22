#include "Map.h"
#include <iostream>
#include "Utility.h"
#include "Controller.h"

Map::Map(string filename)
{
	loadMap(filename);
}

Map::~Map() { }

/*void Map::Update(Hero& hero, float elapsedTime)
{

} */
void Map::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	// draw game objects
	for (vector<list<GameObject*>>::iterator tile = _game_objects.begin(); tile != _game_objects.end(); ++tile)
		for (list<GameObject*>::iterator obj = tile->begin(); obj != tile->end(); ++obj)
			(*obj)->Update(ctrl, localmap, elapsedTime);
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
	for (vector<list<GameObject*>>::iterator tile = _game_objects.begin(); tile != _game_objects.end(); ++tile)
		for (list<GameObject*>::iterator obj = tile->begin(); obj != tile->end(); ++obj)
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
	//loadLayer(mapfile, _top);

	mapfile.close();
}

void Map::loadLayer(std::ifstream& mapfile, vector<Tile>& layer, sf::Texture& tileset)
{
	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;

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

