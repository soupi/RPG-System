#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"

class GameMenu : public State
{
public:
	GameMenu() { init(); }
	virtual void Enter(shared_ptr<StateParams>& params) {  }
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	sf::RectangleShape _rect;
	Flag _change_state;

	char _color;
	void init();

};