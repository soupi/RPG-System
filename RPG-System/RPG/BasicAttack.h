#pragma once

#include "Attack.h"
#include "Macros.h"
#include "Utility.h"
#include "Bank.h"
#include "StaticGraphics.h"

class BasicAttack : public Attack
{
public:
	BasicAttack(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) :
	  Attack(stats, BASIC_ATTACK_POWER, atk), _first(true), _life_timer(0.f)
	  { 
		sf::Vector2i loc(1, 1);
		loc += sf::Vector2i(dir);

		setGraphics(new StaticGraphics(&(Bank<sf::Texture>::getInstance().get("resources/art/basicattack.png")), loc, sf::Vector2u(TILE_SIZE,TILE_SIZE)));
		setPos(pos+dir*getSize());
	  }

	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
private:
	float _life_timer;
	bool _first;
};