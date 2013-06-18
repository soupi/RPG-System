#include "Tile.h"

// constructor for tile. gets it's texture and which tile in the texture to set
Tile::Tile(const sf::Texture& texture, int num) : _num(num)
{  
	_sprite.setTexture(texture);
	// calculate the tile
	_sprite.setTextureRect(sf::IntRect(TILE_SIZE*(_num-1) % texture.getSize().x, TILE_SIZE*(TILE_SIZE*(_num-1) /  texture.getSize().x), TILE_SIZE, TILE_SIZE));
	// scale to showing size
	_sprite.scale(float(SCRN_TILE_SIZE)/TILE_SIZE, float(SCRN_TILE_SIZE)/TILE_SIZE);
}