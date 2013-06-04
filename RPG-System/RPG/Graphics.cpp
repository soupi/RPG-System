#include "Graphics.h"
#include "Tile.h"

Graphics::Graphics(const sf::Texture* texture, sf::Vector2i loc_on_texture, const sf::Vector2u& size) : _texture(texture), _loc_on_texture(loc_on_texture), 
	_display(true), _animation(0), _animation_clock(0.f)
{
	_sprite.setTexture(*_texture);
	_sprite.setTextureRect(sf::IntRect(loc_on_texture.x*size.x, loc_on_texture.y * size.y, size.x, size.y));

	_shadow.setRadius(size.x/2.8f);
	_shadow.setPosition(1 + _shadow.getRadius(), 1 + _shadow.getRadius());
	_shadow.setFillColor(sf::Color::Color(0,0,0,170));
	_shadow.setOrigin(_shadow.getRadius(), _shadow.getRadius());
}

Graphics::Graphics()
{
	_shadow.setRadius(SCRN_TILE_SIZE/2.8f);
	_shadow.setPosition(1 + _shadow.getRadius(), 1 + _shadow.getRadius());
	_shadow.setOrigin(_shadow.getRadius(), _shadow.getRadius());
}

void Graphics::Render(sf::RenderWindow& window)
{
	window.draw(_shadow);
	window.draw(_sprite);

}

void Graphics::move(const sf::Vector2f& direction)
{
	_last_pos = _shadow.getPosition();
	//  change animation according to direction
	_sprite.move(direction);
	_shadow.move(direction);
}


void Graphics::setPos(const sf::Vector2f pos)
{
	_last_pos = _shadow.getPosition();
	_shadow.setPosition(pos.x,pos.y);
	_sprite.setPosition(_shadow.getPosition().x - _sprite.getGlobalBounds().width/2,
		_shadow.getPosition().y - _sprite.getGlobalBounds().height + _shadow.getRadius()/2.f);
}

void Graphics::Update()
{
	// animation
}

bool Graphics::checkCollision(sf::FloatRect& box) const
{
	bool f = getCollisionBox().intersects(box);
	return getCollisionBox().intersects(box);
}

sf::FloatRect Graphics::getCollisionBox() const
{
	sf::Vector2f pos = _shadow.getPosition();
	float radius = _shadow.getRadius();
	return _shadow.getGlobalBounds();
}

sf::Vector2f Graphics::getPos() const
{
	return _shadow.getPosition();
}

void Graphics::undo_move()
{
	setPos(_last_pos);
}

sf::Vector2f Graphics::getFacingDirection() const
{
//	sf::Vector2f dir = _shadow.getPosition() - _last_pos;
//	dir.x = (dir.x != 0) ? abs(dir.x)/dir.x : 0;
//	dir.y = (dir.y != 0) ? abs(dir.y)/dir.y : 0;

	return _dir;
}

sf::Vector2f Graphics::getSize() const
{
	return sf::Vector2f(_shadow.getGlobalBounds().width, _shadow.getGlobalBounds().height);
}