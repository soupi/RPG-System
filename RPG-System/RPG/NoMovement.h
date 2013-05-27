#pragma once

#include "Movement.h"

class NoMovement : public Movement
{
public:
	virtual void handleEvents(const Control& controls) { }
	virtual sf::Vector2f Update(LocalMap& localmap, Graphics* _graphics, float elapsedTime) { return getPos(); }
};