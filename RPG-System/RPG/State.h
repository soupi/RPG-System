#pragma once

#include <SFML/Graphics.hpp>

class Controller;

class State 
{
public:
	virtual ~State() {}
	virtual bool Update(Controller&, float elapsedTime) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
};