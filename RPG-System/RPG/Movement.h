// base class for movement strategy

#pragma once

#include "Control.h"
#include "Graphics.h"
#include "Macros.h"

class LocalMap;
class GameObject;

class Movement
{
public:
	Movement(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), float speed = DEFAULT_SPEED) : 
	  _direction(0.f,0.f), _speed(speed), _newpos(true), _init_pos(pos) { }
	virtual ~Movement() { }

	virtual void handleEvents(const Control& controls) = 0;
	virtual void Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime) = 0;
	void setPos(sf::Vector2f pos) { _init_pos = pos; _newpos = true; }


protected:
	sf::Vector2f _direction;
	float _speed;
	sf::Vector2f _init_pos;
	bool _newpos;
};