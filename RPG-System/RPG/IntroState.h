#pragma once

// introduction state.

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "Dialog.h"

using std::shared_ptr;

class IntroState : public State
{
public:
	virtual void Enter(shared_ptr<StateParams>& params) { init(params); }
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	Flag _change_state;
	shared_ptr<Dialog> _dialog; // introduction

	string _map_name;
	unsigned _starting_tile;

	void init(shared_ptr<StateParams>& params);

};