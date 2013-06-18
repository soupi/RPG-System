// Responsible for the main loop and events handle
// contains the window and view, clock, state machine and hero.

#pragma once

#include "StateMachine.h"
#include "Control.h"
#include "Hero.h"

class Controller
{
public:
	Controller();

	void run(); // run main loop
	Hero& getHero() { return _hero; } // get the hero
	StateMachine& getStateMachine() { return _stateMachine; } // get state machine
	sf::RenderWindow& getWindow() { return _window; } // get window
	sf::View& getView() { return _view; } // get view
	bool handleEvents(sf::Event& event);

private:
	sf::RenderWindow _window;
	sf::View _view;
	sf::Clock _clock;
	StateMachine _stateMachine;

	// to ensure no "double press" will happen
	float _A_button_timer;

	Hero _hero;
	Control _controls;

	void initWindow();
	void initStateMachine();
};