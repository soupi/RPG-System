#include "Enemy.h"
#include "HeroCharacter.h"
#include "LocalMap.h"
#include "remObject.h"

void Enemy::attack(const Stats& stats)
{
	_HP -= calcDamage(stats, _stats);
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
		_HP = 30;
	}
}