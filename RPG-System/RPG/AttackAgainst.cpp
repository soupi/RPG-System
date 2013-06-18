#include "AttackAgainst.h"
#include "Attack.h"
#include "Enemy.h"
#include "HeroCharacter.h"

// attackEnemy calls attack on enemies only
void AttackEnemy::act(LocalMap& localmap, Attack& attack, Enemy& obj)
{
	attack.attack(localmap, obj);
}
// AttackHero calls attack on hero only
void AttackHero::act(LocalMap& localmap, Attack& attack, HeroCharacter& obj)
{
	attack.attack(localmap, obj);
}

// AttackAll calls attack on all.
void AttackAll::act(LocalMap& localmap, Attack& attack, Enemy& obj)
{
	attack.attack(localmap, obj);
}

void AttackAll::act(LocalMap& localmap, Attack& attack, HeroCharacter& obj)
{
	attack.attack(localmap, obj);
}