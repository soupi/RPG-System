#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "menu\Menu.h"

class MainMenu : public State
{
public:
	virtual void Enter(shared_ptr<StateParams>& params) { init(params); }
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	shared_ptr<Menu> _menu;

	void init(shared_ptr<StateParams>& params);

};