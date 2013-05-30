#pragma once

#include "Control.h"
#include "Graphics.h"

const unsigned DEFAULT_SPEED = 3; // three tiles per second

class LocalMap;
class GameObject;

class Movement
{
public:
	Movement(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), unsigned speed = DEFAULT_SPEED) : _direction(0.f,0.f), _speed(speed), _newpos(true), _pos(pos) { }
	virtual ~Movement() { }

	virtual void handleEvents(const Control& controls) = 0;
	virtual sf::Vector2f Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime) = 0;
	void setPos(sf::Vector2f pos) { _pos = pos; _newpos = true; }


protected:
	sf::Vector2f _direction;
	unsigned _speed;
	sf::Vector2f _pos;
	sf::Vector2f _lastpos;
	bool _newpos;
};