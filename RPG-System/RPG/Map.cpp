#include "Map.h"
#include <fstream>
#include <iostream>
#include "Utility.h"

Map::Map(string filename) : _tileset(new sf::Texture())
{
	loadMap(filename);
}

Map::~Map() { }

/*void Map::Update(Hero& hero, float elapsedTime)
{

} */
void Map::Update(float elapsedTime)
{

}

void Map::Render(sf::RenderWindow& window)
{
	for (vector<Tile>::iterator tile = _background.begin(); tile != _background.end(); ++tile)
		tile->draw(window);
}

void Map::loadMap(string& filename)
{
	std::ifstream mapfile;
	mapfile.open("resources/" + filename);

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

	string tiles;
	getline(mapfile, tiles);

	loadTexture(*_tileset, tiles);

	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		int tile;
		try {
			mapfile >> tile;
			_background[i] = Tile(_tileset, tile);
			_background[i].setPos(sf::Vector2f((i%size_w)*float(TILE_SIZE), (i/size_w)*float(TILE_SIZE)));
		}
		catch (...) { }
	}
	mapfile.close();
}