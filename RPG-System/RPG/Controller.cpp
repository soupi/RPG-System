#include "Controller.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "LocalMap.h"

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const unsigned FRAME_RATE = 60;

// tile size is 48x48 -> 32*1.5


Controller::Controller() {
	initWindow();
	initStateMachine();
}

void Controller::run()
{
	while (true)
	{
		float deltaTime = _clock.restart().asSeconds();

		sf::Event event;
		if (_window.pollEvent(event))
			if (_stateMachine.handleEvents(event))
				break;

		_stateMachine.Update(*this,deltaTime);

		_window.setView(_view);
		_window.clear();
		_stateMachine.Render(_window);
		_window.display();

		// fps
		if ((deltaTime = _clock.getElapsedTime().asSeconds()) < 1.f/FRAME_RATE)
			sf::sleep(sf::seconds(1.f/FRAME_RATE - deltaTime));
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
	_window.setFramerateLimit(FRAME_RATE);
	

	// create view
	_view.setCenter(WINDOW_W/2.f, WINDOW_H/2.f);
	_view.setSize(float(WINDOW_W), float(WINDOW_H));
	_window.setView(_view);
}

void Controller::initStateMachine()
{
	_stateMachine.Add("mainmenu", new MainMenu);
	_stateMachine.Add("gamemenu", new GameMenu);
	_stateMachine.Add("localmap", new LocalMap);
	_stateMachine.Change("mainmenu");
}