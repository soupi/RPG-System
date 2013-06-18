#include "Enemy.h"
#include "HeroCharacter.h"
#include "LocalMap.h"
#include "remObject.h"
#include "Loot.h"
#include "Controller.h"
#include "addObject.h"
#include "BasicAttack.h"

// attack the enemy
void Enemy::attack(const Stats& stats, int power)
{
	// calculate damage and substruct from _HP
	_HP -= calcDamage(stats, _stats, power);
	// set experience and coins according to the stats of the attacker
	_exp = unsigned(5 * double(_stats.ATK() + _stats.DEF())/(stats.ATK() + stats.DEF()));
	_coins = rand() % stats.LUCK();
}
// when hero steps on enemy, nothing happens
void Enemy::StepOn(LocalMap& localmap, HeroCharacter& obj)
{

}
// attack hero
bool Enemy::act(LocalMap& localmap, HeroCharacter& obj)
{
	// create an attack and add it to the map
	shared_ptr<GameObject> atk(new BasicAttack(getPos(), getFacingDirection(), _stats, new AttackHero));
	localmap.addCommand(shared_ptr<Script>(new addObjScript(localmap, atk, atk->getPos())));
	return true;
}
// update the enemy
void Enemy::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	// movement update and such
	GameObject::Update(ctrl, localmap, elapsedTime);
	
	// if we are dead but aren't pronouced dead yet,
	if (_HP <= 0 && !_dead)
	{
		// pronounce as dead, add loot to map and ask to be removed from the map
		_dead = true;
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
		localmap.addCommand(shared_ptr<Script>(new addObjScript(localmap, shared_ptr<GameObject>(new Loot(_exp, _coins)), getPos())));
	}

	// can only attack once every ENEMY_ATTACK_INTERVAL
	_attack_timer += elapsedTime;
	if (ENEMY_ATTACK_INTERVAL < _attack_timer)
	{
		_attack_timer = 0; // init timer
		// act
		sf::FloatRect box = getCollisionBox();
		box.left += getFacingDirection().x * getSize().x;
		box.top += getFacingDirection().y * getSize().y;
		localmap.Act(*this, box);
	}
}

// render enemy and it's HP bar above it's head.
void Enemy::Render(Controller& ctrl)
{
	_hp_bar.setValue(_HP);
	GameObject::Render(ctrl);
	if (0 < _HP)
		_hp_bar.show(ctrl, getHeadPos()-sf::Vector2f(0, 10.f));
}