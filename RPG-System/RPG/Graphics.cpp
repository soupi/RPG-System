#include "Graphics.h"
#include "Tile.h"

Graphics::Graphics(sf::Texture* texture, sf::Vector2i loc_on_texture, const sf::Vector2u& size) : _texture(texture), _loc_on_texture(loc_on_texture), 
	_display(true), _animation(0), _animation_clock(0.f)
{
	_sprite.setTexture(*_texture);
	_sprite.setTextureRect(sf::IntRect(loc_on_texture.x, loc_on_texture.y, size.x, size.y));

	_shadow.setRadius(size.x/2.5f);
	_shadow.setFillColor(sf::Color::Color(0,0,0,100));
	_shadow.setOrigin(_shadow.getRadius(), _shadow.getRadius());
}

void Graphics::Render(sf::RenderWindow& window)
{
	window.draw(_shadow);
	window.draw(_sprite);

}

void Graphics::move(const sf::Vector2f& direction)
{
	//  change animation according to direction
	_sprite.move(direction);
	_shadow.move(direction);
}


void Graphics::setPos(const sf::Vector2f& pos)
{
	_sprite.setPosition(pos.x, pos.y);
	// middle point on the bottom of the sprite will be the source of the circle
	_shadow.setPosition(_sprite.getPosition().x+_sprite.getGlobalBounds().width/2, 
		_sprite.getPosition().y + _sprite.getGlobalBounds().height);
}

void Graphics::Update()
{
	// animation
}