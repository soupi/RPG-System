#include "Graphics.h"
#include "Tile.h"
#include "Macros.h"


// constructor: gets the texture, location on texture and size
Graphics::Graphics(const sf::Texture* texture, sf::Vector2i loc_on_texture, const sf::Vector2u& size) : _loc_on_texture(loc_on_texture), 
	_display(true), _animation(0), _animation_clock(0.f)
{
	// set sprite and shadow
	_sprite.setTexture(*texture);
	_sprite.setTextureRect(sf::IntRect(loc_on_texture.x*size.x, loc_on_texture.y * size.y, size.x, size.y));
	_sprite.scale(float(SCRN_TILE_SIZE)/TILE_SIZE, float(SCRN_TILE_SIZE)/TILE_SIZE); // scale to screen
	_shadow.setRadius(_sprite.getGlobalBounds().width/2.8f);
	_shadow.setPosition(1 + _shadow.getRadius(), 1 + _shadow.getRadius());
	_shadow.setFillColor(sf::Color::Color(0,0,0,170));
	_shadow.setOrigin(_shadow.getRadius(), _shadow.getRadius());
}

// default constructor (protected)
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

// move sprite in that direction
void Graphics::move(const sf::Vector2f& direction)
{
	_last_pos = _shadow.getPosition(); // remember last position
	
	// move
	_sprite.move(direction);
	_shadow.move(direction);
}

// setting a new pos
void Graphics::setPos(const sf::Vector2f pos)
{
	// remember position 
	_last_pos = _shadow.getPosition();
	// set new position
	_shadow.setPosition(pos.x,pos.y);
	_sprite.setPosition(_shadow.getPosition().x - _sprite.getGlobalBounds().width/2,
				_shadow.getPosition().y - _sprite.getGlobalBounds().height + _shadow.getRadius()/2.f);
}


// update graphics
void Graphics::Update(float deltaTime)
{
	// animation
	_animation_clock += deltaTime;

	// get facing direction and cut texture accordingly
	sf::Vector2f direction = getFacingDirection();
	unsigned dir;

	dir = DOWN_DIR;
	if (direction.y > 0)
		dir = DOWN_DIR;
	else if (direction.y < 0)
		dir = UP_DIR;
	else if (direction.x > 0)
		dir = RIGHT_DIR;
	else if (direction.x < 0)
		dir = LEFT_DIR;

	// cut texture by direction
	_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left, _loc_on_texture.y*_sprite.getTextureRect().height + _sprite.getTextureRect().height * dir,
		_sprite.getTextureRect().width, _sprite.getTextureRect().height));

	// animate movement
	if (_animation_clock > ANIMATION_SPEED)
	{
		if (_sprite.getTextureRect().width > 0) // avoid dividing by zero (modulo)
			_sprite.setTextureRect(sf::IntRect(_loc_on_texture.x*_sprite.getTextureRect().width + (((_sprite.getTextureRect().left - _loc_on_texture.x*_sprite.getTextureRect().width) + _sprite.getTextureRect().width) % (3*_sprite.getTextureRect().width)),
				 _sprite.getTextureRect().top, _sprite.getTextureRect().width, _sprite.getTextureRect().height));
		_animation_clock = 0.f;
	}
}

// check collision with sprite
bool Graphics::checkCollision(sf::FloatRect& box) const
{
	return getCollisionBox().intersects(box);
}
// get shadows collision box
sf::FloatRect Graphics::getCollisionBox() const
{
	return _shadow.getGlobalBounds();
}
// get current position
sf::Vector2f Graphics::getPos() const
{
	return _shadow.getPosition();
}
// set pos as last position
void Graphics::undo_move()
{
	setPos(_last_pos);
}
// get cuurently facing direction
sf::Vector2f Graphics::getFacingDirection() const
{
	return _dir;
}
// get the size of the shadow
sf::Vector2f Graphics::getSize() const
{
	return sf::Vector2f(_shadow.getGlobalBounds().width, _shadow.getGlobalBounds().height);
}