#include "Enemy.h"
#include "HeroCharacter.h"
#include "LocalMap.h"
#include "remObject.h"
#include "Loot.h"
#include "Controller.h"
#include "addObject.h"
#include "BasicAttack.h"

void Enemy::attack(const Stats& stats, int power)
{
	_HP -= calcDamage(stats, _stats, power);
	_exp = unsigned(5 * double(_stats.ATK() + _stats.DEF())/(stats.ATK() + stats.DEF()));
	_coins = rand() % stats.LUCK();
}

void Enemy::StepOn(LocalMap& localmap, HeroCharacter& obj)
{
	//obj.attack(_stats, 5);

}

void Enemy::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	GameObject::Update(ctrl, localmap, elapsedTime);
	if (_HP <= 0)
	{
		localmap.addCommand(shared_ptr<Script>(new remObjScript(localmap, this)));
		localmap.addCommand(shared_ptr<Script>(new addObjScript(localmap, shared_ptr<GameObject>(new Loot(_exp, _coins)), getPos())));
	}
	_attack_timer += elapsedTime;
	if (1.f < _attack_timer)
	{
		_attack_timer = 0;
		localmap.addCommand(shared_ptr<Script>(new addObjScript(localmap, shared_ptr<GameObject>(new BasicAttack(getPos(), getFacingDirection(), _stats, new AttackHero)), getPos())));
	}
}

void Enemy::Render(Controller& ctrl)
{
	
	_hp_bar.setValue(_HP);
	GameObject::Render(ctrl);
	if (0 < _HP)
		_hp_bar.show(ctrl, getHeadPos()-sf::Vector2f(0, 10.f));
}