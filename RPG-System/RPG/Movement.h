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
	Movement(float speed = DEFAULT_SPEED) : _direction(0.f,0.f), _speed(speed) { }
	virtual ~Movement() { }
	virtual void handleEvents(const Control& controls) = 0;
	virtual bool Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime) = 0;

protected:
	sf::Vector2f _direction;
	float _speed;

};