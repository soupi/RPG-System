#pragma once

#include "HeroCharacter.h"
#include "UserMovement.h"
#include "Utility.h"
#include "Controller.h"
#include "LocalMap.h"

const float HURT_TIME = 1.f;

HeroCharacter::HeroCharacter(shared_ptr<HeroData>& data) : _act(false), _clock(0.f), _hero_data(data)
{
	loadTexture(_hero_texture, "char.png");
	GameObject::setGraphics(new Graphics(&_hero_texture, sf::Vector2i(0,0), sf::Vector2u(64,96)));
	GameObject::setMovement(new UserMovement);
}

void HeroCharacter::handleEvents(const Control& controls)
{
	GameObject::handleEvents(controls);
	if (_clock > PRESS_INTERVAL && controls.isPressed(A))
	{
		_act = true;
		_clock = 0.f;
	}
}
void HeroCharacter::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	_clock += elapsedTime;
	if (_hurt_timer > 0.f)
		_hurt_timer -= elapsedTime;
	GameObject::Update(ctrl, localmap, elapsedTime);
	
	ctrl.getView().setCenter(getPos());
	if (_act)
	{
		_act = false;
		sf::FloatRect box = getGraphics()->getCollisionBox();
		box.left += getGraphics()->getFacingDirection().x * getGraphics()->getSize().x;
		box.top += getGraphics()->getFacingDirection().y * getGraphics()->getSize().y;

		localmap.map()->Act(localmap, *this, box);
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

void HeroCharacter::act(LocalMap& localmap, LocalObject& obj)
{
	obj.act(localmap, *this);
}

void HeroCharacter::attack(Stats& stats)
{
	if (_hurt_timer <= 0)
	{
		_hero_data->takeDamage(calcDamage(stats, _hero_data->getStats()));
		_hurt_timer = HURT_TIME;
	}
}