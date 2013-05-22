#pragma once

#include <SFML\Graphics.hpp>
#include "Control.h"
#include "Movement.h"
#include "NoMovement.h"
#include "Graphics.h"
#include "NoGraphics.h"

class Controller;
class LocalMap;

class GameObject
{
public:
	GameObject(Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement);
	virtual ~GameObject();
	virtual void handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	virtual void Render(Controller& ctrl);

	void setGraphics(Graphics* new_graphics);
	void setMovement(Movement* new_Movement);

	sf::Vector2f getPos() const { return _movement->getPos(); }

private:
	Graphics* _graphics;
	Movement* _movement;
};