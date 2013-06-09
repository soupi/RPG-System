#include "Enemy.h"
#include "HeroCharacter.h"
#include "LocalMap.h"
#include "remObject.h"
#include "Loot.h"
#include "Controller.h"

void Enemy::attack(const Stats& stats)
{
	_HP -= calcDamage(stats, _stats);
	_exp = unsigned(5 * double(_stats.ATK() + _stats.DEF())/(stats.ATK() + stats.DEF));
	_coins = rand() % stats.LUCK();
}

void Enemy::StepOn(LocalMap& localmap, HeroCharacter& obj)
{
	obj.attack(_stats);
}

void Enemy::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	GameObject::Update(ctrl, localmap, elapsedTime);
	if (_HP <= 0)
	{
		localmap.addScript(shared_ptr<Script>(new remObjScript(localmap, this)));
		localmap.addGameObject(shared_ptr<GameObject>(new Loot(_exp, _coins)), getPos());
		_HP = 30;
	}
}