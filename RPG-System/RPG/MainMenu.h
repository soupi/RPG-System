#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "DialogBox.h"

class MainMenu : public State
{
public:
	MainMenu() : _dbox("Welcome to the game!\nPlease Enjoy it!") { }
	virtual State* Enter(StateParams* params = NULL) { init(); return this; }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	sf::RectangleShape _rect;
	Flag _change_state;

	DialogBox _dbox;

	char _color;
	void init();

};