#include "HeroData.h"
#include "HeroCharacter.h"
#include "Controller.h"
#include "LocalMap.h"
#include "Dialog.h"
#include <cmath>
#include "AttackFactory.h"
#include "BulletAttack.h"

using std::string;

// show HP bar
void HeroData::showHP(Controller& ctrl)
{
	// set value to current _HP
	_HP_bar.setValue(_HP);

	// get position
	sf::Vector2f init_window_pos = ctrl.getView().getCenter() - sf::Vector2f(ctrl.getView().getSize().x/2, ctrl.getView().getSize().y/2);
	sf::Vector2f position = init_window_pos + sf::Vector2f(20,20); // + margin

	// show
	_HP_bar.show(ctrl, position);
}

// take damage, ouch!
void HeroData::takeDamage(unsigned amount) 
{ 
	_HP -= amount; 
	if (_HP < 0) // try to regenerate
	{ 
		_HP = 0; 
		--_extra_Lives;
		if (isAlive())
			_HP = BASE_HP; // regenerate
	}
}

// check if we have enough exp to raise to the next level (will check when Loot is called)
void HeroData::checkLevelRaise(LocalMap& map, HeroCharacter& hero_char)
{
	// check raise
	for (;_level < _exp/pow(2.f,int(_level)); ++_level)
	{
		Stats raise = _stats.Raise(); // raise stats
		stringstream ss; // write message on raise
		ss << "You have been raised to level " << _level+1 << "!\nCongratulations!";
		ss << std::endl << "ATK + " << raise.ATK() << "  |  DEF + " << raise.DEF() << "  |  LUCK + " << raise.LUCK();
		if (_level+1 == LEARN_BULLET_ATTACK_LEVEL) // add a new attack when reach to a certain level
		{
			hero_char.addNewAttack(shared_ptr<AttackFactory>(new AttackFactoryT<BulletAttack>));
			ss << "\nYou have learned a new Attack: Bullet!";
		}
		string str(ss.str());
		map.addScript(shared_ptr<Script>(new Dialog(str))); // write the message
	}

}