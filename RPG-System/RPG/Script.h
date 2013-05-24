#pragma once

#include "Hero.h"

class Script 
{
public:
	virtual ~Script() {}
	virtual void Enter(Hero& hero) = 0;
	virtual bool handleEvents(const Control& controls) = 0;
	virtual bool Update(Controller&, float elapsedTime) = 0;
	virtual void Render(Controller& ctrl) = 0;
	virtual void Exit() = 0;
private:
	bool _continue;
};
