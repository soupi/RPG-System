#include "Graphics.h"

Graphics::Graphics(sf::Texture* texture, sf::Vector2i loc_on_texture, const sf::Vector2u& size) : _texture(texture), _loc_on_texture(loc_on_texture), 
	_display(true), _animation(0), _animation_clock(0.f)
{
	_sprite.setTexture(*_texture);
	_sprite.setTextureRect(sf::IntRect(loc_on_texture.x, loc_on_texture.y, size.x, size.y));
}

void Graphics::Render(sf::RenderWindow& window)
{
	window.draw(_sprite);

}

void Graphics::move(const sf::Vector2f& direction)
{
	//  change animation according to direction
	_sprite.move(direction);
}

void Graphics::setPos(const sf::Vector2f& pos)
{
	_sprite.setPosition(pos.x, pos.y);
}

void Graphics::Update()
{

}