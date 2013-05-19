#pragma once

#include <SFML\Graphics.hpp>
#include "Control.h"

#include "Action.h"
#include "NoAction.h"
#include "Movement.h"
#include "NoMovement.h"
#include "Graphics.h"
#include "NoGraphics.h"

class Controller;
class Map;

class GameObject
{
public:
	GameObject(Action* action = new NoAction, Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement);
	virtual ~GameObject();
	virtual void handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, Map& map, float elapsedTime);
	virtual void Render(sf::RenderWindow& window);

	void setAction(Action* new_action);
	void setGraphics(Graphics* new_graphics);
	void setMovement(Movement* new_Movement);

	sf::Vector2f getPos() const { return _movement->getPos(); }

private:
	Action* _action;
	Graphics* _graphics;
	Movement* _movement;
};