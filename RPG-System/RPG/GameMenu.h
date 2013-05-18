#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"

class GameMenu : public State
{
public:
	GameMenu() { init(); }
	virtual State* Enter(StateParams* params = NULL) { return this; }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(sf::RenderWindow& window);

private:
	sf::RectangleShape _rect;
	Flag _change_state;

	char _color;
	void init();

};