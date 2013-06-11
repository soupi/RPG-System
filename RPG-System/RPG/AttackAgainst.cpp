#include "AttackAgainst.h"
#include "Attack.h"
#include "Enemy.h"
#include "HeroCharacter.h"

void AttackEnemy::act(LocalMap& localmap, Attack& attack, Enemy& obj)
{
	attack.attack(localmap, obj);
}

void AttackHero::act(LocalMap& localmap, Attack& attack, HeroCharacter& obj)
{
	attack.attack(localmap, obj);
}

void AttackAll::act(LocalMap& localmap, Attack& attack, Enemy& obj)
{
	attack.attack(localmap, obj);
}

void AttackAll::act(LocalMap& localmap, Attack& attack, HeroCharacter& obj)
{
	attack.attack(localmap, obj);
}