#pragma once

#include "Attack.h"
#include "Macros.h"
#include "Utility.h"
#include "DirMovement.h"
#include "Bank.h"

class BulletAttack : public Attack
{
public:
	BulletAttack(const sf::Vector2f& pos, sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) :
	  Attack(stats, 5, atk, new Graphics(&(Bank<sf::Texture>::getInstance().get("char.png")), sf::Vector2i(0,0), sf::Vector2u(30,30)), 
		  new DirMovement(dir, DEFAULT_SPEED*4.f)) 
	  {
		//  (dir.x != 0 && dir.y != 0) ? sf::Vector2f(0, dir.y) : dir /* none diagonal moving */   ????
		//  if (dir.x != 0 && dir.y != 0)
		// 	  dir.x = 0;
		  setPos(pos+dir*getSize()*2.f); 
	  }

	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
};