#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"

class Pause : public State
{
public:
	Pause() { init(); }
	virtual void Enter(shared_ptr<StateParams>& params) {  }
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	sf::Text _text;
	Flag _change_state;

	void init();

};