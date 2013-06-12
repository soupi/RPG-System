// graphics representation class.  also holds the location on the window

#pragma once

#include <SFML\Graphics.hpp>
#include "Macros.h"

class Graphics
{
public:
	Graphics(const sf::Texture* texture, sf::Vector2i loc_on_texture, const sf::Vector2u& size);
	virtual ~Graphics() { }
	virtual void Update(float elapsedTime);
	virtual void Render(sf::RenderWindow& window);
	// ----------------
	void move(const sf::Vector2f& direction);
	void setPos(const sf::Vector2f pos);
	void undo_move();
	sf::Vector2f getPos() const;
	void setDir(sf::Vector2f& dir) { _dir = dir; }
	// ----------------
	float getRadius() const { return _shadow.getRadius(); }
	void setDisplay(bool dis);
	bool checkCollision(sf::FloatRect& box) const;
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getFacingDirection() const;
	sf::Vector2f getSize() const;
	const sf::Vector2f& getHeadPos() const { return _sprite.getPosition(); }

protected:
	Graphics();
	

private:
	const sf::Texture* _texture;
	sf::Sprite _sprite;
	sf::CircleShape _shadow;
	sf::Vector2f _last_pos;
	sf::Vector2f _dir;

	sf::Vector2i _loc_on_texture;
	unsigned _animation;
	float _animation_clock;
	bool _display;
};