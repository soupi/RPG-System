#include "Attack.h"
#include "LocalObject.h"
#include "LocalMap.h"
#include "remObject.h"

// interact with local object
bool Attack::act(LocalMap& localmap, LocalObject& obj)
{
	return false;
}

// interact with enemy
bool Attack::act(LocalMap& localmap, Enemy& obj)
{
	// attack if attack hurts enemies
	_atk->act(localmap, *this, obj);
	return true;
}
// interact with hero
bool Attack::act(LocalMap& localmap, HeroCharacter& obj)
{
	// attack if attack hurts hero
	_atk->act(localmap, *this, obj);
	return true;
}
// attack enemy
void Attack::attack(LocalMap& localmap, Enemy& obj)
{
	obj.attack(_stats, _power);
}
// attack hero
void Attack::attack(LocalMap& localmap, HeroCharacter& obj)
{
	obj.attack(_stats, _power);
}
// don't attack objects.
void Attack::attack(LocalMap& localmap, LocalObject& obj)
{

}

