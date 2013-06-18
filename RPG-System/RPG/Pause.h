#pragma once

// Pause menu called from the game. will let the user go back to the game, view controls or exit.

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "menu/Menu.h"

class Pause : public State
{
public:
	Pause() : _escape(false) {  }
	virtual void Enter(shared_ptr<StateParams>& params) { init(params); }
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

	void escape() { _escape = true; }

private:
	shared_ptr<Menu> _menu;
	bool _escape; // the user wants to escape the program

	void init(shared_ptr<StateParams>& params);

};