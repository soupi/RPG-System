#pragma once

// base class for scripts

#include "Hero.h"

class Script 
{
public:
	Script() : _continue(false), _entered(false) {}
	virtual ~Script() {}

	virtual void Enter(Hero& hero) { _entered = true; _continue = true; enter(hero); }
	virtual bool handleEvents(const Control& controls) = 0;
	virtual bool Update(Controller&, float elapsedTime) = 0;
	virtual void Render(Controller& ctrl) = 0;
	virtual void Exit() { _entered = false; _continue = false; exit(); }
	bool Continue() const { return _continue; }
	bool hasEntered() const { return _entered; }
protected:
	bool _continue; // should we continue running this script?
	bool _entered; // have we entered this script?
private:
	virtual void enter(Hero& hero) = 0;
	virtual void exit() = 0;
};
