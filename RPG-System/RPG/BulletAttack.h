#pragma once

// attack moving toward a given direction. 

#include "Attack.h"
#include "Macros.h"
#include "Utility.h"
#include "DirMovement.h"
#include "Bank.h"

class BulletAttack : public Attack
{
public:
	BulletAttack(const sf::Vector2f& pos, sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) :
	  Attack(stats, BULLET_ATTACK_POWER, atk, new Graphics(&(Bank<sf::Texture>::getInstance().get("resources/art/bullet.png")), sf::Vector2i(0,0), sf::Vector2u(16,16)), 
		  new DirMovement(dir, DEFAULT_SPEED*4.f)) 
	  {
		  setPos(pos+dir*getSize()*2.f); 
	  }

	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);

	virtual bool act(LocalMap& localmap, LocalObject& obj);
	virtual bool act(LocalMap& localmap, Enemy& obj);
	virtual bool act(LocalMap& localmap, HeroCharacter& obj);
};