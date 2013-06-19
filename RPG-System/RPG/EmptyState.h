// this state contains nothing.

#pragma once

#include "State.h"

class EmptyState : public State {
	virtual bool handleEvents(const Control& controls) { return true; } // if reached here, will terminate the program
	virtual void Update(Controller& ctrl, float elapsedTime) { }
	virtual void Render(Controller& ctrl) {}
	virtual void Enter(shared_ptr<StateParams>& params) { }
	virtual void Exit() { }
};