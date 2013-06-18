#pragma once

// creates an attack and returns it when called by get() function.

#include "Attack.h"


// base
class AttackFactory
{
public:
	~AttackFactory() {}
	virtual Attack* get(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) = 0;
};

// derivated. gets ATTACK type as class template
template <class ATK>
class AttackFactoryT : public AttackFactory
{
public:
	virtual Attack* get(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll)
	{
		return new ATK(pos, dir, stats, atk);
	}
};