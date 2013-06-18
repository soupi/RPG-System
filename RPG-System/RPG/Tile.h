#pragma once

// Tile on the tile map

#include <SFML\Graphics.hpp>
#include "Macros.h"

class Tile {
public:
	Tile(const sf::Texture& texture, int num);
	Tile() : _num(0) /* _num = 0 means no tile to display */ { }
	int getNum() const { return _num; }
	void draw(sf::RenderWindow& window) { if (_num) window.draw(_sprite); }
	void setPos(sf::Vector2f pos) { _sprite.setPosition(pos); }

private:
	sf::Sprite _sprite;
	int _num; // num of tile
};