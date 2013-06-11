#pragma once

#include "Attack.h"

class AttackFactory
{
public:
	~AttackFactory() {}
	virtual Attack* get(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) = 0;
};

template <class ATK>
class AttackFactoryT
{
public:
	virtual Attack* get(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll)
	{
		return new ATK(pos, dir, stats, atk);
	}
};