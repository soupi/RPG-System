#pragma once

#include "State.h"

class EmptyState : public State {
	virtual bool handleEvents(const Control& controls) { return false; }
	virtual void Update(Controller& ctrl, float elapsedTime) { }
	virtual void Render(sf::RenderWindow& window) {}
	virtual State* Enter(StateParams* params = NULL) { return this; }
};