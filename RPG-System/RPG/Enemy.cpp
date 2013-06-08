#include "Enemy.h"
#include "HeroCharacter.h"

void Enemy::attack(Stats& stats)
{
	_HP -= calcDamage(stats, _stats);
}

void Enemy::StepOn(LocalMap& localmap, HeroCharacter& obj)
{
	obj.attack(_stats);
}