#pragma once

#include "StateMachine.h"

class Controller
{
public:
	Controller();

	void run();
	// get Hero
	StateMachine& getStateMachine() { return _stateMachine; }
	sf::RenderWindow& getWindow() { return _window; }
	sf::View& getView() { return _view; }

private:
	sf::RenderWindow _window;
	sf::View _view;
	sf::Clock _clock;
	StateMachine _stateMachine;

	// Hero character


	void initWindow();
	void initStateMachine();
};