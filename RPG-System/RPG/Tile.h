#pragma once

#include <SFML\Graphics.hpp>

const unsigned TILE_SIZE = 64;

class Tile {
public:
	Tile(sf::Texture* texture, int num);
	Tile() : _num(0) { }
	int getNum() const { return _num; }
	void draw(sf::RenderWindow& window)
	{
		if (_num)
			window.draw(_sprite);
	}
	void setPos(sf::Vector2f pos) { _sprite.setPosition(pos); }

private:
	sf::Texture* _texture;
	sf::Sprite _sprite;
	int _num;
};