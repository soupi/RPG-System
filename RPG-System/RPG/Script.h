#pragma once

#include "Hero.h"

class Script 
{
public:
	Script() : _continue(false), _entered(false) {}
	virtual ~Script() {}
	virtual void Enter(Hero& hero) { _entered = true; enter(hero); }
	virtual bool handleEvents(const Control& controls) = 0;
	virtual bool Update(Controller&, float elapsedTime) = 0;
	virtual void Render(Controller& ctrl) = 0;
	virtual void Exit() = 0;
	bool Continue() const { return _continue; }
	bool hasEntered() const { return _entered; }
protected:
	bool _continue;
	bool _entered;
private:
	virtual void enter(Hero& hero) = 0;
};
