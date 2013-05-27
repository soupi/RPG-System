#pragma once

#include <SFML\Graphics.hpp>
#include "Control.h"
#include "Movement.h"
#include "NoMovement.h"
#include "Graphics.h"
#include "NoGraphics.h"

class Controller;
class LocalMap;

using std::shared_ptr;

const float speed = 250.f;


class GameObject
{
public:
	GameObject(Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement);
	virtual ~GameObject();
	virtual void handleEvents(const Control& controls);
	virtual sf::Vector2f Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	virtual void Render(Controller& ctrl);

	void setGraphics(Graphics* new_graphics);
	void setMovement(Movement* new_Movement);

	sf::Vector2f getPos() const { return _movement->getPos(); }
	void setPos(sf::Vector2f pos) { _movement->setPos(pos); }

	// double dispatch
	virtual void Interact(LocalMap& localmap, GameObject& obj) { obj.Interact(localmap, *this); }
	virtual void StepOn(LocalMap& localmap, GameObject& obj) = 0;
	virtual bool canStepOn(GameObject& obj) = 0;

private:
	shared_ptr<Graphics> _graphics;
	shared_ptr<Movement> _movement;
};