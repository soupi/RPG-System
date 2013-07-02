#include "Controller.h"
#include "MainMenu.h"
#include "Pause.h"
#include "LocalMap.h"
#include "Splash.h"
#include "ParamsCtrl.h"
#include "Macros.h"
#include "Help.h"
#include "GameOverState.h"
#include "ScrolledUpTextState.h"
#include "IntroState.h"
#include <memory>
#include "Bank.h"

using std::shared_ptr; 


// Constructor for controller
Controller::Controller() : _A_button_timer(0.f), _ENTER_button_timer(0.f)  {
	initWindow();
	initStateMachine();
}

// main loop
void Controller::run()
{
	while (true)
	{
		// time since last loop
		float deltaTime = _clock.restart().asSeconds();

		_A_button_timer += deltaTime;
		_ENTER_button_timer += deltaTime;
		// handle events
		sf::Event event;
		if (_window.pollEvent(event))
		{
			// close game indicators
			if (handleEvents(event)) 
				break; 
			else if (_stateMachine.handleEvents(_controls))
				break;
		}

		// is hero is dead change state to game over
		if (!_hero.isAlive())
			_stateMachine.Change("gameover", shared_ptr<StateParams>( new ParamsCtrl(*this)));

		// Update
		_stateMachine.Update(*this,deltaTime);

		// Render
		_window.setView(_view);
		_window.clear();
		_stateMachine.Render(*this);
		_window.display();

		// fps
		if ((deltaTime = _clock.getElapsedTime().asSeconds()) < 1.f/FRAME_RATE)
			sf::sleep(sf::seconds(1.f/FRAME_RATE - deltaTime));
	}
	shared_ptr<StateParams> params( new ParamsCtrl(*this));
	_stateMachine.Change("pause", params);
}

// creates controls from events
bool Controller::handleEvents(sf::Event& event)
{
	// holds controls
	bool controls[NUM_OF_CONTROLS] = { false };
	if (event.type == sf::Event::Closed)
		return true;

	// check mouse button
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
			controls[MOUSE_SECONDARY] = true;
			
		if (event.mouseButton.button == sf::Mouse::Left)
			controls[MOUSE_PRIMARY] = true;
	}

	// set keyboard controls: arrows
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		controls[RIGHT] = true;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		controls[LEFT] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		controls[UP] = true;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		controls[DOWN] = true;
	// set keyboard controls: action keys
	if (_A_button_timer > PRESS_INTERVAL && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		controls[A] = true;
		_A_button_timer = 0.f;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		controls[B] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		controls[C] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		controls[D] = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		if (PRESS_INTERVAL < _ENTER_button_timer)
		{
			controls[ENTER] = true;
			_ENTER_button_timer = 0.f;
		}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		controls[PAUSE] = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		controls[ESC] = true;

	// set current controls
	_controls.setControls(controls);

	return false;
}

// init window
void Controller::initWindow() 
{
	// create window, size and settings
	sf::ContextSettings settings;
	//settings.antialiasingLevel = 4;
	
	double ratio = double(sf::VideoMode::getDesktopMode().height)/sf::VideoMode::getDesktopMode().width;

	_window.create(sf::VideoMode(WINDOW_W, unsigned(WINDOW_W*ratio)), 
		"Little Adventure", sf::Style::Fullscreen, settings);

	// icon
	sf::Image icon = Bank<sf::Image>::getInstance().get("resources/icon.png");
	_window.setIcon(32, 32, icon.getPixelsPtr());

	_window.setVerticalSyncEnabled(true); // set refresh rate as screen's refresh rate
	_window.setJoystickThreshold(10000); // joystick threshold
	_window.setFramerateLimit(FRAME_RATE); // and frame rate
	
	_window.setMouseCursorVisible(false); // hide mouse

	// create view
	_view.setCenter(_window.getSize().x/2.f, _window.getSize().y/2.f);
	_view.setSize(float(_window.getSize().x), float(_window.getSize().y));
	_window.setView(_view);
}

// creates states and add them to state machine
void Controller::initStateMachine()
{
	_stateMachine.Add("mainmenu", shared_ptr<State>(new MainMenu));
	_stateMachine.Add("pause", shared_ptr<State>(new Pause));
	_stateMachine.Add("help", shared_ptr<State>(new Help));
	_stateMachine.Add("gameover", shared_ptr<State>(new GameOver));
	_stateMachine.Add("localmap", shared_ptr<State>(new LocalMap));
	_stateMachine.Add("splash", shared_ptr<State>(new Splash));
	_stateMachine.Add("intro", shared_ptr<State>(new IntroState));
	_stateMachine.Add("credits", shared_ptr<State>(new ScrolledUpTextState(CREDITS)));

	// change to splash state
	shared_ptr<StateParams> params( new ParamsCtrl(*this));
	_stateMachine.Stack("splash", params);
}