#include "AttackAgainst.h"
#include "Attack.h"
#include "Enemy.h"
#include "HeroCharacter.h"

void AttackEnemy::StepOn(LocalMap& localmap, Attack& attack, Enemy& obj)
{
	attack.attack(localmap, obj);
}

void AttackHero::StepOn(LocalMap& localmap, Attack& attack, HeroCharacter& obj)
{
	attack.attack(localmap, obj);
}

void AttackAll::StepOn(LocalMap& localmap, Attack& attack, Enemy& obj)
{
	attack.attack(localmap, obj);
}

void AttackAll::StepOn(LocalMap& localmap, Attack& attack, HeroCharacter& obj)
{
	attack.attack(localmap, obj);
}