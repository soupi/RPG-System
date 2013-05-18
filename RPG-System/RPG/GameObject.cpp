#include "GameObject.h"
#include "Controller.h"
#include "Map.h"
#include "Control.h"

GameObject::GameObject(Action* action, Graphics* graphics, Movement* movement) : 
				_action(action), _graphics(graphics), _movement(movement)
{

}

GameObject::~GameObject()
{
	delete _action;
	delete _graphics;
	delete _movement;
}

// handle events 
void GameObject::handleEvents(const Control& controls)
{
	if (_movement)
		_movement->handleEvents(controls);
	if (_action)
		_action->handleEvents(controls);
}

void GameObject::Update(Controller& ctrl, Map& map, float elapsedTime)
{
	if (_action)
		_action->Update(ctrl, map, elapsedTime, _movement);
	if (_movement)
		_movement->Update(_graphics, elapsedTime);
}

void GameObject::Render(sf::RenderWindow& window)
{
	if (_graphics)
		_graphics->Render(window);
}



void GameObject::setAction(Action* new_action)
{
	delete _action;
	_action = new_action;
}
void GameObject::setGraphics(Graphics* new_graphics)
{
	delete _graphics;
	_graphics = new_graphics;
}
void GameObject::setMovement(Movement* new_movement)
{
	delete _movement;
	_movement = new_movement;
}