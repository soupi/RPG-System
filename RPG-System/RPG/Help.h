#pragma once

// help state shows the controls

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"

class Help : public State
{
public:
	Help() { init(); }
	virtual void Enter(shared_ptr<StateParams>& params);
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	sf::Sprite _key_layout;
	Flag _pop;

	void init();

};