#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"

class GameMenu : public State
{
public:
	virtual State* Enter(StateParams* params = NULL) { init(); return this; }
	virtual bool Update(Controller& ctrl, float elapsedTime);
	virtual void Render(sf::RenderWindow& window);

private:
	sf::RectangleShape _rect;
	char _color;
	void init();

};