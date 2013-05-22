#include "GameObject.h"
#include "Controller.h"
#include "LocalMap.h"
#include "Control.h"

GameObject::GameObject(Graphics* graphics, Movement* movement) : 
				 _graphics(graphics), _movement(movement)
{

}

GameObject::~GameObject()
{
	delete _graphics;
	delete _movement;
}

// handle events 
void GameObject::handleEvents(const Control& controls)
{
	if (_movement)
		_movement->handleEvents(controls);
}

void GameObject::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	if (_movement)
		_movement->Update(localmap, _graphics, elapsedTime);
}

void GameObject::Render(Controller& ctrl)
{
	if (_graphics)
		_graphics->Render(ctrl.getWindow());
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