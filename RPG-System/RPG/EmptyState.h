#pragma once

#include "State.h"

class EmptyState : public State {
	virtual bool handleEvents(const Control& controls) { return false; }
	virtual void Update(Controller& ctrl, float elapsedTime) { }
	virtual void Render(Controller& ctrl) {}
	virtual State* Enter(shared_ptr<StateParams>& params) { return this; }
};