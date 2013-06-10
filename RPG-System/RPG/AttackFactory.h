#pragma once

#include "Attack.h"

class AttackFactory
{
public:
	~AttackFactory() {}
	virtual Attack* get(Stats stats, AttackAgainst* atk) = 0;
};

template <class ATK>
class AttackFactoryT
{
public:
	virtual Attack* get(Stats stats, AttackAgainst* atk)
	{
		return new ATK(stats, atk);
	}
private:
	ATK atk;
};