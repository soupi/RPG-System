#pragma once

#include "Control.h"
#include "Graphics.h"

const unsigned DEFAULT_SPEED = 3; // three tiles per second


class Movement
{
public:
	Movement(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), unsigned speed = DEFAULT_SPEED) : _direction(0.f,0.f), _speed(speed), _newpos(true), _pos(pos) { }
	~Movement() { }

	virtual void handleEvents(const Control& controls) { }
	virtual void Update(Graphics* _graphics, float elapsedTime) { }
	sf::Vector2f getPos() const { return _pos; }
	void setPos(sf::Vector2f pos) { _pos = pos; _newpos = true; }

protected:
	sf::Vector2f _direction;
	unsigned _speed;
	sf::Vector2f _pos;
	bool _newpos;
};