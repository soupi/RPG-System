#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"

class MainMenu : public State
{
public:
	MainMenu(StateParams* params = NULL) { init(); }
	virtual bool Update(Controller& ctrl, float elapsedTime);
	virtual void Render(sf::RenderWindow& window);

private:
	sf::RectangleShape _rect;
	char _color;
	void init();

};