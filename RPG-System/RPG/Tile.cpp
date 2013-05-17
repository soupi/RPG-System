#include "Tile.h"

Tile::Tile(sf::Texture* texture, int num) : _texture(texture), _num(num)
{  
	_sprite.setTexture(*_texture);
		
	_sprite.setTextureRect(sf::IntRect(TILE_SIZE*((_num-1) % _texture->getSize().x), TILE_SIZE*((_num-1) /  _texture->getSize().x), TILE_SIZE, TILE_SIZE));
	//_sprite.scale(TILE_SIZE/float(BTN_SIZE), TILE_SIZE/float(BTN_SIZE));
	sf::IntRect ra = _sprite.getTextureRect();
	
}