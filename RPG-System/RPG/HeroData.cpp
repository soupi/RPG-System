#include "HeroData.h"
#include "Controller.h"

void HeroData::showHP(Controller& ctrl)
{
	_HP_bar.setValue(_HP);

	sf::Vector2f init_window_pos = ctrl.getView().getCenter() - sf::Vector2f(ctrl.getView().getSize().x/2, ctrl.getView().getSize().y/2);
	sf::Vector2f position = init_window_pos + sf::Vector2f(20,20);

	_HP_bar.show(ctrl, position);
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