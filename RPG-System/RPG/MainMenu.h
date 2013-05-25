#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "Dialog.h"

class MainMenu : public State
{
public:
	MainMenu() : _dialog("Welcome to a new game made by WhiteStar Games! I hope you'll enjoy it as much as i enjoyed making it!\nHave Fun!") { }
	virtual State* Enter(StateParams* params = NULL) { init(); return this; }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	sf::RectangleShape _rect;
	Flag _change_state;

	Dialog _dialog;

	char _color;
	void init();

};