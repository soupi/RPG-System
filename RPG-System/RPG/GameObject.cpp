#include "GameObject.h"
#include "Controller.h"
#include "LocalMap.h"
#include "Control.h"


// Constructor
GameObject::GameObject(Graphics* graphics, Movement* movement) : 
				 _graphics(graphics), _movement(movement), _id(0), _moved(false)
{

}

// handle events 
void GameObject::handleEvents(const Control& controls)
{
	_movement->handleEvents(controls);
}

// update object
void GameObject::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	// updates the movement
	_moved = _movement->Update(localmap, *this, *_graphics, elapsedTime);
}

// render object
void GameObject::Render(Controller& ctrl)
{
	_graphics->Render(ctrl.getWindow());
}

// sets new graphics and movements
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

//bool GameObject::checkCollision(sf::FloatRect& box) const { return _graphics->checkCollision(box); }
	