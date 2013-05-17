#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"

class MainMenu : public State
{
public:
	virtual State* Enter(StateParams* params = NULL) { init(); return this; }
	virtual bool handleEvents(sf::Event& event);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(sf::RenderWindow& window);

private:
	sf::RectangleShape _rect;
	Flag _change_state;

	char _color;
	void init();

};