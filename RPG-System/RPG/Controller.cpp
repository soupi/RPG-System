#include "Controller.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "LocalMap.h"

const int WINDOW_W = 1024;
const int WINDOW_H = 768;


Controller::Controller() {
	initWindow();
	initStateMachine();
}

void Controller::run()
{
	while (true)
	{
		float deltaTime = _clock.restart().asSeconds();
		if (_stateMachine.Update(*this,deltaTime))
			break;
		_stateMachine.Render(_window);
		_window.display();
	}
}

void Controller::initWindow() 
{
	// create window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	_window.create(sf::VideoMode(WINDOW_W, WINDOW_H), 
					"RPG", sf::Style::Default, settings);
	
	_window.setVerticalSyncEnabled(true); // set refresh rate as screen's refresh rate
	_window.setJoystickThreshold(10000); // joystick threshold
}

void Controller::initStateMachine()
{
	_stateMachine.Add("mainmenu", new StateFactory<MainMenu>);
	_stateMachine.Add("gamemenu", new GameMenu);
	_stateMachine.Add("localmap", new LocalMap);
	_stateMachine.Change("mainmenu");
}