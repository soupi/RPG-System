#include "HeroCharacter.h"
#include "UserMovement.h"
#include "Utility.h"
#include "Controller.h"
#include "LocalMap.h"
#include "Enemy.h"
#include "AttackAgainst.h"
#include "addObject.h"
#include "Bank.h"

const float HURT_TIME = 1.f;

HeroCharacter::HeroCharacter(shared_ptr<HeroData>& data) : _act(false), _B_clock(0.f), _hero_data(data), _curr_attack(0)
{
	GameObject::setGraphics(new Graphics(&(Bank<sf::Texture>::getInstance().get("resources/art/chara01.png")), sf::Vector2i(0,0), sf::Vector2u(32,48)));
	GameObject::setMovement(new UserMovement);

	_atks.push_back(shared_ptr<AttackFactory>(new AttackFactoryT<BasicAttack>));
}

void HeroCharacter::handleEvents(const Control& controls)
{
	GameObject::handleEvents(controls);
	if (controls.isPressed(A))
		_act.set();
	
	if (_B_clock > PRESS_INTERVAL)
	{
		if (controls.isPressed(C))
			_curr_attack = (_curr_attack - 1) % _atks.size();
		if (controls.isPressed(D))
			_curr_attack = (_curr_attack + 1) % _atks.size();
		_B_clock = 0.f;
	}
}
void HeroCharacter::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	_B_clock += elapsedTime;

	if (_hurt_timer > 0.f)
		_hurt_timer -= elapsedTime;

	GameObject::Update(ctrl, localmap, elapsedTime);
	
	ctrl.getView().setCenter(getPos());

	if (_act.state())
	{
		sf::FloatRect box = getCollisionBox();
		box.left += getFacingDirection().x * getSize().x;
		box.top += getFacingDirection().y * getSize().y;
		if (!localmap.Act(*this, box))
		{
			shared_ptr<GameObject> atk(_atks[_curr_attack]->get(getPos(), getFacingDirection(), _hero_data->getStats(), new AttackEnemy));
			localmap.addCommand(shared_ptr<Script>(new addObjScript(localmap, atk, atk->getPos())));
		}
	}
}

void HeroCharacter::giveQuestItem(QuestItem& item) 
{  
	_hero_data->addQuestItem(item);
}
bool HeroCharacter::hasQuestItem(const string& item_name) 
{
	return _hero_data->hasQuestItem(item_name);
}

bool HeroCharacter::act(LocalMap& localmap, LocalObject& obj)
{
	return obj.act(localmap, *this);
}

bool HeroCharacter::act(LocalMap& localmap, Enemy& obj)
{
	return false;
}
void HeroCharacter::attack(const Stats& stats, int power)
{
	if (_hurt_timer <= 0)
	{
		_hero_data->takeDamage(calcDamage(stats, _hero_data->getStats(), power));
		_hurt_timer = HURT_TIME;
	}
}

void HeroCharacter::addNewAttack(shared_ptr<AttackFactory> atk)
{
	_atks.push_back(atk);
}