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

	void run();
	Hero& getHero() { return _hero; }
	StateMachine& getStateMachine() { return _stateMachine; }
	sf::RenderWindow& getWindow() { return _window; }
	sf::View& getView() { return _view; }
	bool handleEvents(sf::Event& event);

private:
	sf::RenderWindow _window;
	sf::View _view;
	sf::Clock _clock;
	StateMachine _stateMachine;

	Hero _hero;
	Control _controls;

	void initWindow();
	void initStateMachine();
};