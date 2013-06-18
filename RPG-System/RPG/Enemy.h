#pragma once

// an enemy for battles against.

#include "GameObject.h"
#include "Attack.h"
#include "Stats.h"
#include "Bar.h"

class Enemy : public GameObject
{
public:
	Enemy(Graphics* graphics = new NoGraphics, Movement* movement = new NoMovement, Stats stats = Stats(), unsigned HP = 100) : 
	  GameObject(graphics, movement), _HP(HP), _stats(stats), _attack_timer(0.f), _dead(false),
		  _hp_bar(HP, sf::Vector2f(graphics->getRadius()*3.f,graphics->getRadius()/1.5f)) {}

	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	virtual void Render(Controller& ctrl);

	virtual bool act(LocalMap& localmap, GameObject& obj) { return obj.act(localmap, *this); }
	virtual void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	virtual bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	virtual bool canStepOn(LocalObject& obj) { return false; }
	virtual bool canStepOn(HeroCharacter& obj) { return false; }
	virtual bool canStepOn(Enemy& obj) { return true; }
	virtual bool canStepOn(Attack& obj) { return true; }

	virtual bool act(LocalMap& localmap, HeroCharacter& hero);
	virtual void StepOn(LocalMap& localmap, HeroCharacter& obj);
	
	void attack(const Stats& stats, int power); // enemy is attacked
private:
	// parameters
	int _HP;
	Stats _stats;
	unsigned _exp, _coins;
	bool _dead;

	Bar _hp_bar;
	float _attack_timer;
	
};