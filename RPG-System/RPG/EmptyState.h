#pragma once

#include "State.h"

class EmptyState : public State {
	virtual bool Update(Controller& ctrl, float elapsedTime) { return false; }
	virtual void Render(sf::RenderWindow& window) {}
	virtual State* Enter(StateParams* params = NULL) { return this; }
};