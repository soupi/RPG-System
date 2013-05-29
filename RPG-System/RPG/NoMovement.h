#pragma once

#include "Movement.h"

class NoMovement : public Movement
{
public:
	virtual void handleEvents(const Control& controls) { }
	virtual sf::Vector2f Update(LocalMap& localmap, Graphics* _graphics, float elapsedTime) 
	{
		if (_newpos)
		{
			if (_graphics)
				_graphics->setPos(_pos);

			_newpos = false; 
		}
		return getPos(); 
	}
};