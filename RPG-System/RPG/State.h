#pragma once

#include <SFML/Graphics.hpp>
#include "StateParams.h"

class Controller;

class State 
{
public:
	virtual ~State() {}
	virtual bool Update(Controller&, float elapsedTime) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual State* Enter(StateParams* params = NULL) = 0;
	virtual bool Exit() { return false; }
};