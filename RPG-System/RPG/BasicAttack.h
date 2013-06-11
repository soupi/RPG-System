#pragma once

#include "Attack.h"
#include "Macros.h"
#include "Utility.h"

class BasicAttack : public Attack
{
public:
	BasicAttack(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) :
		Attack(stats, 10, atk) { setPos(pos+dir*getSize()); }

	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
};