// base class state for states in state machine

#pragma once

#include <SFML/Graphics.hpp>
#include "StateParams.h"
#include "Control.h"
#include <memory>

using std::shared_ptr;

class Controller;

class State 
{
public:
	virtual ~State() {}
	virtual bool handleEvents(const Control& controls) = 0;
	virtual void Update(Controller&, float elapsedTime) = 0;
	virtual void Render(Controller& ctrl) = 0;
	virtual void Enter(shared_ptr<StateParams>& params) = 0;
	virtual void Exit() = 0;
};