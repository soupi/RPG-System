#include "HeroData.h"

void HeroData::showHP(Controller& ctrl)
{
	_HP_bar.setValue(_HP);
	_HP_bar.show(ctrl, sf::Vector2f(20,20));
}

void HeroData::takeDamage(unsigned amount) 
{ 
	_HP -= amount; 
	if (_HP < 0)
	{ 
		_HP = 0; 
		--_Lives;
		if (isAlive())   
			_HP = BASE_HP; 
	}
}