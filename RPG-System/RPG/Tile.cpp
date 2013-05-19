#include "Tile.h"

Tile::Tile(sf::Texture* texture, int num) : _texture(texture), _num(num)
{  
	_sprite.setTexture(*_texture);
		
	_sprite.setTextureRect(sf::IntRect(TILE_SIZE*(_num-1) % _texture->getSize().x, TILE_SIZE*(TILE_SIZE*(_num-1) /  _texture->getSize().x), TILE_SIZE, TILE_SIZE));
	_sprite.scale(float(SCRN_TILE_SIZE)/TILE_SIZE, float(SCRN_TILE_SIZE)/TILE_SIZE);
	
}