#include "HeroCharacter.h"
#include "UserMovement.h"
#include "Utility.h"
#include "Controller.h"
#include "LocalMap.h"
#include "Enemy.h"
#include "AttackAgainst.h"
#include "addObject.h"
#include "Bank.h"

const float HURT_TIME = 1.f; // we cannot be hit after a hit during this time

// constructor: needs the hero's data.
HeroCharacter::HeroCharacter(shared_ptr<HeroData>& data) : _act(false), _B_clock(0.f), _hero_data(data), _curr_attack(0)
{
	// set my strategies
	GameObject::setGraphics(new Graphics(&(Bank<sf::Texture>::getInstance().get("resources/art/chara01.png")), sf::Vector2i(0,0), sf::Vector2u(TILE_SIZE,unsigned(TILE_SIZE * 1.5))));
	GameObject::setMovement(new UserMovement);

	// set my basic attack
	_atks.push_back(shared_ptr<AttackFactory>(new AttackFactoryT<BasicAttack>));
}

// handle events
void HeroCharacter::handleEvents(const Control& controls)
{
	GameObject::handleEvents(controls);

	// act if A is pressed
	if (controls.isPressed(A))
		_act.set();
	
	// switch attack if C or D are pressed and they have not been pressed for PRESS_INTERVAL
	if (_B_clock > PRESS_INTERVAL)
	{
		if (controls.isPressed(C))
			_curr_attack = (_curr_attack - 1) % _atks.size();
		if (controls.isPressed(D))
			_curr_attack = (_curr_attack + 1) % _atks.size();
		_B_clock = 0.f;
	}
}

// update
void HeroCharacter::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	_B_clock += elapsedTime;

	if (_hurt_timer > 0.f) // counting backwards
		_hurt_timer -= elapsedTime;

	GameObject::Update(ctrl, localmap, elapsedTime);
	
	// I am the center of the game.
	ctrl.getView().setCenter(getPos());

	// if A was pressed
	if (_act.state())
	{
		// act or attack if there is nothing to interact with
		sf::FloatRect box = getCollisionBox(); // the box in my direction
		box.left += getFacingDirection().x * getSize().x;
		box.top += getFacingDirection().y * getSize().y;
		if (!localmap.Act(*this, box)) // if there is not interaction
		{
			// create an obj of current marked attack
			shared_ptr<GameObject> atk(_atks[_curr_attack]->get(getPos(), getFacingDirection(), _hero_data->getStats(), new AttackEnemy));
			// add it to local map
			localmap.addCommand(shared_ptr<Script>(new addObjScript(localmap, atk, atk->getPos())));
		}
	}
}

// the hero receives a quest item
void HeroCharacter::giveQuestItem(QuestItem& item) 
{  
	_hero_data->addQuestItem(item);
}
// does the hero has the quest item?
bool HeroCharacter::hasQuestItem(const string& item_name) 
{
	return _hero_data->hasQuestItem(item_name);
}
// interact with local object
bool HeroCharacter::act(LocalMap& localmap, LocalObject& obj)
{
	return obj.act(localmap, *this);
}
// interact with enemy
bool HeroCharacter::act(LocalMap& localmap, Enemy& obj)
{
	return false; // no interaction. only death.
}

// attacked
void HeroCharacter::attack(const Stats& stats, int power)
{
	// will not hurt if we are right after a previous hit
	if (_hurt_timer <= 0)
	{
		_hero_data->takeDamage(calcDamage(stats, _hero_data->getStats(), power));
		_hurt_timer = HURT_TIME;
	}
}
// add a new attack to arsenal
void HeroCharacter::addNewAttack(shared_ptr<AttackFactory>& atk)
{
	_atks.push_back(atk);
}