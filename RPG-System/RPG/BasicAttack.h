#pragma once

#include "Attack.h"
#include "Macros.h"
#include "LocalMap.h"
#include "remObject.h"

class BasicAttack : public Attack
{
	BasicAttack(const sf::Vector2f pos, const sf::Vector2f dir, Stats stats, AttackAgainst* atk = new AttackAll) :
		Attack(stats, 10, atk) { setPos(pos+dir*float(SCRN_TILE_SIZE)); }

	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
	{
		sf::FloatRect box = getCollisionBox();
		localmap.Act(*this, box);
		localmap.addScript(shared_ptr<Script>(new remObjScript(localmap, this)));
	}
};