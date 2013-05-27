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

}

// handle events 
void GameObject::handleEvents(const Control& controls)
{
	_movement->handleEvents(controls);
}

sf::Vector2f GameObject::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	return _movement->Update(localmap, &(*_graphics), elapsedTime);
}

void GameObject::Render(Controller& ctrl)
{
	_graphics->Render(ctrl.getWindow());
}

void GameObject::setGraphics(Graphics* new_graphics)
{
	if (new_graphics)
		_graphics = shared_ptr<Graphics>(new_graphics);
}
void GameObject::setMovement(Movement* new_movement)
{
	if (new_movement)
		_movement = shared_ptr<Movement>(new_movement);
}