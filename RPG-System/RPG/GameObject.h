#pragma once

#include <SFML\Graphics.hpp>
#include "Control.h"
#include "Movement.h"
#include "NoMovement.h"
#include "Graphics.h"
#include "NoGraphics.h"
#include <memory>

class Controller;
class LocalMap;
class HeroCharacter;
class LocalObject;
class Enemy;

using std::shared_ptr;

const float speed = 250.f;


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

	sf::Vector2f getPos() const { return _graphics->getPos(); }
	void setPos(sf::Vector2f pos) { _movement->setPos(pos); }
	
	bool checkCollision(sf::FloatRect& box);

	shared_ptr<Graphics>& getGraphics() { return _graphics; }

	// interaction using double dispatch


	virtual void act(LocalMap& localmap, GameObject& obj) = 0;
	virtual void StepOn(LocalMap& localmap, GameObject& obj) = 0;
	virtual bool canStepOn(GameObject& obj) = 0;

	// default for heroCharacter
	virtual void act(LocalMap& localmap, HeroCharacter&) { }
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) {}
	virtual bool canStepOn(HeroCharacter&) { return true; } 
	// default for LocalObject
	virtual void act(LocalMap& localmap, LocalObject&) { }
	virtual void StepOn(LocalMap& localmap, LocalObject&) {}
	virtual bool canStepOn(LocalObject&) { return true; } 
	// default for Enemy
	virtual void act(LocalMap& localmap, Enemy&) { }
	virtual void StepOn(LocalMap& localmap, Enemy&) {}
	virtual bool canStepOn(Enemy&) { return true; } 

private:
	shared_ptr<Graphics> _graphics;
	shared_ptr<Movement> _movement;
};