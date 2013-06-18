// base class for game objects.

#pragma once

#include <SFML\Graphics.hpp>
#include "Control.h"
#include "Movement.h"
#include "NoMovement.h"
#include "Graphics.h"
#include "NoGraphics.h"
#include <memory>

// forward declarations
class Controller;
class LocalMap;
class HeroCharacter;
class LocalObject;
class Enemy;
class Attack;

using std::shared_ptr;

class GameObject
{
public:
	// constructor: needs the graphics and the movement of the object
	GameObject(Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement);
	virtual ~GameObject() {}
	// basic interface
	virtual void handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	virtual void Render(Controller& ctrl);

	// change the graphics and movement
	void setGraphics(Graphics* new_graphics);
	void setMovement(Movement* new_Movement);

	// graphics functions
	const sf::Vector2f getPos() const { return _graphics->getPos(); }
	void setPos(sf::Vector2f pos) { _graphics->setPos(pos); }
	float getRadius() const { return _graphics->getRadius(); }
	bool checkCollision(sf::FloatRect& box) const { return _graphics->checkCollision(box); }
	sf::FloatRect getCollisionBox() const { return _graphics->getCollisionBox(); }
	const sf::Vector2f getFacingDirection() const { return _graphics->getFacingDirection(); }
	const sf::Vector2f getSize() const { return _graphics->getSize(); }
	// position of the head of the sprite
	const sf::Vector2f& getHeadPos() const { return _graphics->getHeadPos(); }
	void UpdateGraphics(float elapsedTime) { _graphics->Update(elapsedTime); }

	// id
	int getId() const { return _id; }
	virtual void setId(int id) { _id = id; }
	
	// interaction using double dispatch
	virtual bool act(LocalMap& localmap, GameObject& obj) = 0;
	virtual void StepOn(LocalMap& localmap, GameObject& obj) = 0;
	virtual bool canStepOn(GameObject& obj) = 0;

	// default for heroCharacter
	virtual bool act(LocalMap& localmap, HeroCharacter&) { return false; }
	virtual void StepOn(LocalMap& localmap, HeroCharacter&) {}
	virtual bool canStepOn(HeroCharacter&) { return true; } 
	// default for LocalObject
	virtual bool act(LocalMap& localmap, LocalObject&) { return false; }
	virtual void StepOn(LocalMap& localmap, LocalObject&) {}
	virtual bool canStepOn(LocalObject&) { return true; } 
	// default for Enemy
	virtual bool act(LocalMap& localmap, Enemy&) { return false; }
	virtual void StepOn(LocalMap& localmap, Enemy&) {}
	virtual bool canStepOn(Enemy&) { return true; }
	// default for Attack
	virtual void StepOn(LocalMap& localmap, Attack& obj) {}
	virtual bool canStepOn(Attack& obj) { return true; }
	virtual bool act(LocalMap& localmap, Attack& obj) { return false; }

private:
	// strategy pattern
	shared_ptr<Graphics> _graphics;
	shared_ptr<Movement> _movement;

	int _id;

protected:
	bool _moved; // has the object moved?
};